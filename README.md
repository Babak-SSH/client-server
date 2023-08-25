# Client-Server with Protobuf

This project is a simple client server with Google Protobuf

This repository contains an example of how to setup a cpp TCP server and client for sending and receiving Protobuf messages.

## Requirements

- protobuf 3.12.x
- cpp 17

## Example

there is simple example in test directory which you can build with:
``` bash
./build.sh
```
or running the commands manually.

this example works in localhost but you can alter the ips to make it work with 2 different devices with tcp connection:
``` bash
cd build
./tcp_server
```
``` bash
cd build
./tcp_client
```
this example demonstrates sending 500 continuous fake imu(xyz and rpy) data with 1 millis timeout between them and finally sending a png image (reading the image from build/client_data and receiving in build/server_data). 

you can change the message types and send any form of data with this method.