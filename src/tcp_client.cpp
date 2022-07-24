#include <netdb.h>
#include <unistd.h>


#include "../include/tcp_client.h"
#include "../include/file_descriptor.h"


namespace TCP {
    TcpClient::TcpClient() {
        _isConnected = false;
        _isClosed = true;
    }

    TcpClient::~TcpClient() {
        close();
    }

    ret_st TcpClient::connectTo(const std::string & address, int port) {
        try {
            initializeSocket();
            setAddress(address, port);
        } catch (const std::runtime_error& error) {
            return ret_st::failure(error.what());
        }

        const int connectResult = connect(_sockfd.get() , (struct sockaddr *)&_server , sizeof(_server));
        const bool connectionFailed = (connectResult == -1);
        if (connectionFailed) {
            return ret_st::failure(strerror(errno));
        }

        startReceivingMessages();
        _isConnected = true;
        _isClosed = false;

        return ret_st::success();
    }

    void TcpClient::startReceivingMessages() {
        _receiveTask = new std::thread(&TcpClient::receiveTask, this);
    }

    void TcpClient::initializeSocket() {
        ret_st ret;

        _sockfd.set(socket(AF_INET , SOCK_STREAM , 0));
        const bool socketFailed = (_sockfd.get() == -1);
        if (socketFailed) {
            throw std::runtime_error(strerror(errno));
        }
    }

    void TcpClient::setAddress(const std::string& address, int port) {
        const int inetSuccess = inet_aton(address.c_str(), &_server.sin_addr);

        if(!inetSuccess) { // inet_addr failed to parse address
            // if hostname is not in IP strings and dots format, try resolve it
            struct hostent *host;
            struct in_addr **addrList;
            /// @todo replace it with getaddrinfo() (gethotbyname is deprecated and doesnt support ipv6)
            if ( (host = gethostbyname( address.c_str() ) ) == nullptr){ throw std::runtime_error("Failed to resolve hostname"); } addrList = (struct in_addr **) host->h_addr_list; _server.sin_addr = *addrList[0];
        }
        _server.sin_family = AF_INET;
        _server.sin_port = htons(port);
    }


    ret_st TcpClient::sendMsg(const char * msg, size_t size) {
        const size_t numBytesSent = send(_sockfd.get(), msg, size, 0);

        if (numBytesSent < 0 ) { // send failed
            return ret_st::failure(strerror(errno));
        }
        if (numBytesSent < size) { // not all bytes were sent
            char errorMsg[100];
            sprintf(errorMsg, "Only %lu bytes out of %lu was sent to client", numBytesSent, size);
            return ret_st::failure(errorMsg);
        }
        return ret_st::success();
    }

    // void TcpClient::subscribe(const client_observer_t & observer) {
    //     std::lock_guard<std::mutex> lock(_subscribersMtx);
    //     _subscibers.push_back(observer);
    // }

    /*
     * Publish incomingPacketHandler client message to observer.
     * Observers get only messages that originated
     * from clients with IP address identical to
     * the specific observer requested IP
     */
    // void TcpClient::publishServerMsg(const char * msg, size_t msgSize) {
    //     std::lock_guard<std::mutex> lock(_subscribersMtx);
    //     for (const auto &subscriber : _subscibers) {
    //         if (subscriber.incomingPacketHandler) {
    //             subscriber.incomingPacketHandler(msg, msgSize);
    //         }
    //     }
    // }

    /*
     * Publish client disconnection to observer.
     * Observers get only notify about clients
     * with IP address identical to the specific
     * observer requested IP
     */
    // void TcpClient::publishServerDisconnected(const ret_st & ret) {
    //     std::lock_guard<std::mutex> lock(_subscribersMtx);
    //     for (const auto &subscriber : _subscibers) {
    //         if (subscriber.disconnectionHandler) {
    //             subscriber.disconnectionHandler(ret);
    //         }
    //     }
    // }

    /*
     * Receive server packets, and notify user
     */
    void TcpClient::receiveTask() {
        while(_isConnected) {
            const FileDesc::Result waitResult = FileDesc::waitFor(_sockfd);

            if (waitResult == FileDesc::Result::FAILURE) {
                throw std::runtime_error(strerror(errno));
            } else if (waitResult == FileDesc::Result::TIMEOUT) {
                continue;
            }

            char msg[MAX_PACKET_SIZE];
            const size_t numOfBytesReceived = recv(_sockfd.get(), msg, MAX_PACKET_SIZE, 0);

            if(numOfBytesReceived < 1) {
                std::string errorMsg;
                if (numOfBytesReceived == 0) { //server closed connection
                    errorMsg = "Server closed connection";
                } else {
                    errorMsg = strerror(errno);
                }
                _isConnected = false;
                // publishServerDisconnected(ret_st::failure(errorMsg));
                return;
            } else {
                // publishServerMsg(msg, numOfBytesReceived);
            }
        }
    }

    void TcpClient::terminateReceiveThread() {
        _isConnected = false;

        if (_receiveTask) {
            _receiveTask->join();
            delete _receiveTask;
            _receiveTask = nullptr;
        }
    }

    ret_st TcpClient::close(){
        if (_isClosed) {
            return ret_st::failure("client is already closed");
        }
        terminateReceiveThread();

        const bool closeFailed = (::close(_sockfd.get()) == -1);
        if (closeFailed) {
            return ret_st::failure(strerror(errno));
        }
        _isClosed = true;
        return ret_st::success();
    }
}