#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdio.h>
#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <chrono>
#include <pthread.h>
#include <thread>
#include <mutex>
#include <atomic>

#include "file_descriptor.h"
#include "utils.h"


namespace TCP {

class TcpClient {
    private:
        FileDesc::FileDescriptor _sockfd;
        std::atomic<bool> _isConnected;
        std::atomic<bool> _isClosed;
        struct sockaddr_in _server;
        //std::vector<client_observer_t> _subscibers;
        std::thread * _receiveTask = nullptr;
        std::mutex _subscribersMtx;

        void initializeSocket();
        void startReceivingMessages();
        void setAddress(const std::string& address, int port);
        //void publishServerMsg(const char * msg, size_t msgSize);
        //void publishServerDisconnected(const ret_st & ret);
        void receiveTask();
        void terminateReceiveThread();

    public:
        TcpClient();
        ~TcpClient();
        ret_st connectTo(const std::string & address, int port);
        ret_st sendMsg(const char * msg, size_t size);

        //void subscribe(const client_observer_t & observer);
        bool isConnected() const { return _isConnected; }
        ret_st close();

}; 

} // namespace TCP

#endif