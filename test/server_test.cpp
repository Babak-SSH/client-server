#include "../include/tcp_server.h"


TCP::TcpServer server;

TCP::server_observer_t observer1;

// observer callback. will be called for every new message received by clients
// with the requested IP address
void onIncomingMsg1(const std::string &clientIP, const char * msg, size_t size) {
    std::string msgStr = msg;
    // print client message
    std::cout << "Observer1 got client msg: " << msgStr << "\n";
}

// observer callback. will be called when client disconnects
void onClientDisconnected(const std::string &ip, const std::string &msg) {
    std::cout << "Client: " << ip << " disconnected. Reason: " << msg << "\n";
}

void acceptClient() {
    try {
        std::cout << "waiting for incoming client...\n";
        std::string clientIP = server.acceptClient(0);
        std::cout << "accepted new client with IP: " << clientIP << "\n" <<
                  "== updated list of accepted clients ==" << "\n";
        server.printClients();
    } catch (const std::runtime_error &error) {
        std::cout << "Accepting client failed: " << error.what() << "\n";
    }
}

int main() {
    TCP::ret_st startRet = server.start(5005);

    if (startRet.isSuccessful()) {
        std::cout << "Server setup succeeded\n";
    } else {
        std::cout << "Server setup failed: " << startRet.message() << "\n";
        return EXIT_FAILURE;
    }

    // configure and register observer1
    observer1.incomingPacketHandler = onIncomingMsg1;
    observer1.disconnectionHandler = onClientDisconnected;
    observer1.wantedIP = "127.0.0.1";
    server.subscribe(observer1);

    while(true) {
        acceptClient();
    }

    return 0;
}