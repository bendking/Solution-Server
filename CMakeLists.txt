cmake_minimum_required(VERSION 3.13)
project(Solution_Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(Server)

add_executable(Solution_Server
        Server/MySerialServer.cpp
        Server/MySerialServer.h
        Server/Server.h
        ClientHandler/ClientHandler.h
        ClientHandler/MyTestClientHandler.cpp
        ClientHandler/MyTestClientHandler.h
        Server/InputStream.cpp
        Server/InputStream.h
        Server/OutputStream.cpp
        Server/OutputStream.h)
