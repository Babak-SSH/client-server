#include <cerrno>
#include <cstring>
#include <cstdio>

#include <stdexcept>
#include <unistd.h>

#include <iostream>

#include <sys/socket.h>

#include "../include/client.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/any.pb.h>


using namespace google::protobuf::io;

namespace TCP {

    Client::Client(int fileDescriptor) {
        _sockfd.set(fileDescriptor);
        setConnected(false);
    }

    bool Client::operator==(const Client & other) const {
        if ((this->_sockfd.get() == other._sockfd.get()) &&
            (this->_ip == other._ip) ) {
            return true;
        }
        return false;
    }

    void Client::startListen() {
        std::cout << "start to listen....." << std::endl;
        setConnected(true);
        _receiveThread = new std::thread(&Client::receiveTask, this);
    }

    void Client::send(const char *msg, size_t msgSize) const {
        const size_t numBytesSent = ::send(_sockfd.get(), (char *)msg, msgSize, 0);

        const bool sendFailed = (numBytesSent < 0);
        if (sendFailed) {
            throw std::runtime_error(strerror(errno));
        }

        const bool notAllBytesWereSent = (numBytesSent < msgSize);
        if (notAllBytesWereSent) {
            char errorMsg[100];
            sprintf(errorMsg, "Only %lu bytes out of %lu was sent to client", numBytesSent, msgSize);
            throw std::runtime_error(errorMsg);
        }
    }

    static google::protobuf::uint32 readHdr(char *buf) {
        google::protobuf::uint32 size;
        google::protobuf::io::ArrayInputStream ais(buf,4);
        CodedInputStream coded_input(&ais);
        coded_input.ReadVarint32(&size);//Decode the HDR and get the size
        std::cout<<"size of payload is "<<size<<std::endl;
        return size;
    }

    static google::protobuf::Any readBody(int csock,google::protobuf::uint32 siz) {
        int bytecount;
        google::protobuf::Any any;
        char buffer [siz+4];//size of the payload and hdr
        
        //Read the entire buffer including the hdr
        if((bytecount = recv(csock, (void *)buffer, 4+siz, MSG_WAITALL)) == -1){
            fprintf(stderr, "Error receiving data %d\n", errno);
        }

        std::cout<<"Second read byte count is "<<bytecount<<std::endl;
        //Assign ArrayInputStream with enough memory 
        google::protobuf::io::ArrayInputStream ais(buffer,siz+4);
        CodedInputStream coded_input(&ais);

        //Read an unsigned integer with Varint encoding, truncating to 32 bits.
        coded_input.ReadVarint32(&siz);

        //After the message's length is read, PushLimit() is used to prevent the CodedInputStream 
        //from reading beyond that length.Limits are used when parsing length-delimited 
        //embedded messages
        google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);

        //De-Serialize
        any.ParseFromCodedStream(&coded_input);

        coded_input.PopLimit(msgLimit);

        return any;
   }

    /*
     * Receive client packets, and notify user
     */
    void Client::receiveTask() {
        while(isConnected()) {
            const FileDesc::Result waitResult = FileDesc::waitFor(_sockfd);

            if (waitResult == FileDesc::Result::FAILURE) {
                throw std::runtime_error(strerror(errno));
            }
            else if (waitResult == FileDesc::Result::TIMEOUT) {
                continue;
            }

            char receivedMessage[MAX_PACKET_SIZE];
            google::protobuf::Any payload;

            ///@todo use MSG_PEEK flag
            // const size_t numOfBytesReceived = recv(_sockfd.get(), receivedMessage, MAX_PACKET_SIZE, 0);
            const size_t numOfBytesReceived = recv(_sockfd.get(), receivedMessage, 4, MSG_PEEK);

            if(numOfBytesReceived < 1) {
                const bool clientClosedConnection = (numOfBytesReceived == 0);
                std::string disconnectionMessage;

                if (clientClosedConnection) {
                    disconnectionMessage = "Client closed connection";
                } 
                else {
                    disconnectionMessage = strerror(errno);
                }

                setConnected(false);
                publishEvent(ClientEvent::DISCONNECTED, payload, disconnectionMessage);
                return;
            }
            else {
                payload = readBody(_sockfd.get(),readHdr(receivedMessage));
                publishEvent(ClientEvent::INCOMING_MSG, payload, "");

                memset(receivedMessage, 0, sizeof(receivedMessage));
            }
        }
    }

    void Client::publishEvent(ClientEvent clientEvent, const google::protobuf::Any data, const std::string &error) {
        _eventHandlerCallback(*this, clientEvent, data, error);
    }

    void Client::print() const {
        const std::string connected = isConnected() ? "True" : "False";
        std::cout << "-----------------\n" <<
                  "IP address: " << getIp() << std::endl <<
                  "Connected?: " << connected << std::endl <<
                  "Socket FD: " << _sockfd.get() << std::endl;
    }

    void Client::terminateReceiveThread() {
        setConnected(false);
        if (_receiveThread) {
            _receiveThread->join();
            delete _receiveThread;
            _receiveThread = nullptr;
        }
    }

    void Client::close() {
        terminateReceiveThread();

        const bool closeFailed = (::close(_sockfd.get()) == -1);
        if (closeFailed) {
            throw std::runtime_error(strerror(errno));
        }
    }
}