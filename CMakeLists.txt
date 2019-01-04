cmake_minimum_required(VERSION 3.13)
project(Solution_Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(ClientHandler)
include_directories(Server)

add_executable(Solution_Server
        ClientHandler/ClientHandler.h
        ClientHandler/MyTestClientHandler.cpp
        ClientHandler/MyTestClientHandler.h
        Server/MySerialServer.cpp
        Server/MySerialServer.h
        Server/Server.h Solver/Solver.h Searcher/StringReverser.cpp Searcher/StringReverser.h main.cpp CacheManager/CacheManager.h CacheManager/FileCacheManager.cpp CacheManager/FileCacheManager.h)
