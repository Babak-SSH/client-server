cmake_minimum_required(VERSION 3.20)
project(server_client)

find_package(Threads)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

add_library(${PROJECT_NAME}
        src/tcp_client.cpp
        src/tcp_server.cpp
        src/client.cpp
        src/utils.cpp
        src/file_descriptor.cpp)

add_executable(tcp_server test/server_test.cpp)

target_link_libraries (tcp_server ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_executable(tcp_client test/client_test.cpp)

target_link_libraries (tcp_client ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})


