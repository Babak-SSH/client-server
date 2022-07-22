#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include <iostream>

#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <chrono>
#include <pthread.h>

#include "file_descriptor.h"
#include "utils.h"


namespace TCP {

class TcpServer {
    private:
        FileDesc::FileDescriptor socket_desc, new_socket, thread_socket;
        struct sockaddr_in _serverAddress, _clientAddress;
        char *message, client_reply[2000];

        // void publishClientMsg(const Client & client, const char * msg, size_t msgSize);
        // void publishClientDisconnected(const std::string&, const std::string&);
        // ret_st waitForClient(uint32_t timeout);
        // void clientEventHandler(const Client&, ClientEvent, const std::string &msg);
        // void removeDeadClients();
        // void terminateDeadClientsRemover();

    public:
        TcpServer();
        ~TcpServer();
        ret_st start(int port);
        void initializeSocket();
        void bindAddress(int port);
        void listenToClients();
        std::string acceptClient(uint timeout);
        //void subscribe(const server_observer_t & observer);
        ret_st sendToAllClients(const char * msg, size_t size);
        ret_st sendToClient(const std::string & clientIP, const char * msg, size_t size);
        ret_st close();
        void printClients();

}; 

} // namespace TCP

#endif