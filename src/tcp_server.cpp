#include "../include/tcp_server.h"


namespace TCP {

    TcpServer::TcpServer() {

    }

    TcpServer::~TcpServer() {
        close();
    }

    void TcpServer::printClients() {

    }

    /// bind port and start listening
    ret_st TcpServer::start(int port) {
        try {
            initializeSocket();
            bindAddress(port);
            listenToClients();
        } catch (const std::runtime_error &error) {
            return ret_st::failure(error.what());
        }
        return ret_st::success();
    }
    
    void TcpServer::initializeSocket() {
        _socketDesc.set(socket(AF_INET, SOCK_STREAM, 0));

        if (_socketDesc.get() == -1) {
            throw std::runtime_error(strerror(errno));
        }

        // set socket for reuse (otherwise might have to wait 4 minutes every time socket is closed)
        const int option = 1;
        setsockopt(_socketDesc.get(), SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    }

    void TcpServer::bindAddress(int port) {
        memset(&_serverAddress, 0, sizeof(_serverAddress));
        _serverAddress.sin_family = AF_INET;
        _serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        _serverAddress.sin_port = htons(port);

        if (bind(_socketDesc.get(), (struct sockaddr *)&_serverAddress, sizeof(_serverAddress))) {
            throw std::runtime_error(strerror(errno));
        }
    }

    void TcpServer::listenToClients() {
        // can be a paramater if wanted to change max connection requests
        const int clientsQueueSize = 3;
        if (listen(_socketDesc.get(), clientsQueueSize) == -1) {
            throw std::runtime_error(strerror(errno));
        }
    }
} // namespace TCP