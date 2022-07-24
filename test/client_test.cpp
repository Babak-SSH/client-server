#include <csignal>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/tcp_client.h"


TCP::TcpClient client;

void sig_exit(int s)
{
	std::cout << "Closing client...\n";
	ret_st finishRet = client.close();
	if (finishRet.isSuccessful()) {
		std::cout << "Client closed.\n";
	} else {
		std::cout << "Failed to close client.\n";
	}
	exit(0);
}

int main() {
    //register to SIGINT to close client when user press ctrl+c
	signal(SIGINT, sig_exit);

    bool connected = false;
    while (!connected) {
        ret_st connectRet = client.connectTo("127.0.0.1", 5005);
        connected = connectRet.isSuccessful();
        if (connected) {
            std::cout << "Client connected successfully\n";
        } else {
            std::cout << "Client failed to connect: " << connectRet.message() << "\n"
                      << "Make sure the server is open and listening\n\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            std::cout << "Retrying to connect...\n";
        }
	};

    // send message
    std::string message = "fuck";
    ret_st sendRet = client.sendMsg(message.c_str(), message.size());
    if (!sendRet.isSuccessful()) {
        std::cout << "Failed to send message: " << sendRet.message() << "\n";
    } else {
        std::cout << "message was sent successfuly\n";
    }
}