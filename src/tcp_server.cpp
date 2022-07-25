#include <functional>
#include <unistd.h>

#include "../include/tcp_server.h"


namespace TCP {

    TcpServer::TcpServer() {
        _clients.reserve(10);
    }

    TcpServer::~TcpServer() {
        close();
    }

    void TcpServer::subscribe(const server_observer_t & observer) {
        std::lock_guard<std::mutex> lock(_subscribersMtx);
        _subscribers.push_back(observer);
    }

    void TcpServer::printClients() {
        std::lock_guard<std::mutex> lock(_clientsMtx);
        if (_clients.empty()) {
            std::cout << "no connected clients\n";
        }
        for (const Client *client : _clients) {
            client->print();
        }
    }

    /**
     * Handle different client events. Subscriber callbacks should be short and fast, and must not
     * call other server functions to avoid deadlock
     */
    void TcpServer::clientEventHandler(const Client &client, ClientEvent event, const std::string &msg) {
        switch (event) {
            case ClientEvent::DISCONNECTED: {
                publishClientDisconnected(client.getIp(), msg);
                break;
            }
            case ClientEvent::INCOMING_MSG: {
                publishClientMsg(client, msg.c_str(), msg.size());
                break;
            }
        }
    }

    /*
     * Publish incomingPacketHandler client message to observer.
     * Observers get only messages that originated
     * from clients with IP address identical to
     * the specific observer requested IP
     */
    void TcpServer::publishClientMsg(const Client & client, const char * msg, size_t msgSize) {
        std::lock_guard<std::mutex> lock(_subscribersMtx);

        for (const server_observer_t& subscriber : _subscribers) {
            if (subscriber.wantedIP == client.getIp() || subscriber.wantedIP.empty()) {
                if (subscriber.incomingPacketHandler) {
                    subscriber.incomingPacketHandler(client.getIp(), msg, msgSize);
                }
            }
        }
    }

    /*
     * Publish client disconnection to observer.
     * Observers get only notify about clients
     * with IP address identical to the specific
     * observer requested IP
     */
    void TcpServer::publishClientDisconnected(const std::string &clientIP, const std::string &clientMsg) {
        std::lock_guard<std::mutex> lock(_subscribersMtx);

        for (const server_observer_t& subscriber : _subscribers) {
            if (subscriber.wantedIP == clientIP) {
                if (subscriber.disconnectionHandler) {
                    subscriber.disconnectionHandler(clientIP, clientMsg);
                }
            }
        }
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

    std::string TcpServer::acceptClient(uint timeout) {
        const ret_st waitingForClient = waitForClient(timeout);
        if (!waitingForClient.isSuccessful()) {
            throw std::runtime_error(waitingForClient.message());
        }

        socklen_t socketSize  = sizeof(_clientAddress);
        const int fileDescriptor = accept(_socketDesc.get(), (struct sockaddr*)&_clientAddress, &socketSize);

        const bool acceptFailed = (fileDescriptor == -1);
        if (acceptFailed) {
            throw std::runtime_error(strerror(errno));
        }

        auto newClient = new Client(fileDescriptor);
        newClient->setIp(inet_ntoa(_clientAddress.sin_addr));
        using namespace std::placeholders;
        newClient->setEventsHandler(std::bind(&TcpServer::clientEventHandler, this, _1, _2, _3));
        newClient->startListen();

        std::lock_guard<std::mutex> lock(_clientsMtx);
        _clients.push_back(newClient);

        return newClient->getIp();
    } 

    ret_st TcpServer::waitForClient(uint32_t timeout) {
    if (timeout > 0) {
        const FileDesc::Result waitResult = FileDesc::waitFor(_socketDesc, timeout);
        const bool noIncomingClient = (!FD_ISSET(_socketDesc.get(), &_fds));

        if (waitResult == FileDesc::Result::FAILURE) {
            return ret_st::failure(strerror(errno));
        } else if (waitResult == FileDesc::Result::TIMEOUT) {
            return ret_st::failure("Timeout waiting for client");
        } else if (noIncomingClient) {
            return ret_st::failure("File descriptor is not set");
        }
    }

    return ret_st::success();
}

    /*
     * Send message to all connected clients.
     * Return true if message was sent successfully to all clients
     */
    ret_st TcpServer::sendToAllClients(const char * msg, size_t size) {
        std::lock_guard<std::mutex> lock(_clientsMtx);
    
        for (const Client *client : _clients) {
            ret_st sendingResult = sendToClient(*client, msg, size);
            if (!sendingResult.isSuccessful()) {
                return sendingResult;
            }
        }
    
        return ret_st::success();
    }
    
    /*
     * Send message to specific client (determined by client IP address).
     * Return true if message was sent successfully
     */
    ret_st TcpServer::sendToClient(const Client & client, const char * msg, size_t size){
        try{
            client.send(msg, size);
        } catch (const std::runtime_error &error) {
            return ret_st::failure(error.what());
        }
    
        return ret_st::success();
    }
    
    /*
     * Close server and clients resources.
     * Return true is successFlag, false otherwise
     */
    ret_st TcpServer::close() {
        //terminateDeadClientsRemover();
        { // close clients
            std::lock_guard<std::mutex> lock(_clientsMtx);
    
            for (Client * client : _clients) {
                try {
                    client->close();
                } catch (const std::runtime_error& error) {
                    return ret_st::failure(error.what());
                }
            }
            _clients.clear();
        }
    
        { // close server
            const int closeServerResult = ::close(_socketDesc.get());
            const bool closeServerFailed = (closeServerResult == -1);
            if (closeServerFailed) {
                return ret_st::failure(strerror(errno));
            }
        }
    
        return ret_st::success();
    }
} // namespace TCP