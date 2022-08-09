#include <csignal>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>

#include "../include/tcp_client.h"
#include "../protos/out/IMU_data.pb.h"
#include "../protos/out/img_data.pb.h"


TCP::TcpClient client;

void sig_exit(int s)
{
	std::cout << "Closing client...\n";
	TCP::ret_st finishRet = client.close();
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

    float count = 0;

    bool connected = false;
    while (!connected) {
        TCP::ret_st connectRet = client.connectTo("127.0.0.1", 5005);
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

    while (count < 500) {
        IMU::IMU_data payload;

        payload.set_roll(10);
        payload.set_pitch(5);
        payload.set_acc_x(count);
        payload.set_acc_y(count);
        payload.set_acc_z(4);

        // send message
        TCP::ret_st sendRet = client.sendData<IMU::IMU_data>(payload);

        count++;

        if (!sendRet.isSuccessful()) {
            std::cout << "Failed to send message: " << sendRet.message() << "\n";
        } else {
            std::cout << "message was sent successfuly\n";
        }   
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    Image::img_data imgPayload;

    auto [imgSize, imgData] = client.encodeFile("/home/babak-ssh/temp/11.jpg");

    imgPayload.set_img(imgData);
    imgPayload.set_size(imgSize);

    TCP::ret_st sendRet = client.sendData<Image::img_data>(imgPayload);   

}