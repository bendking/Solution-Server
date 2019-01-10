cmake_minimum_required(VERSION 3.13)
project(Solution_Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(ClientHandler)
include_directories(Server)

add_executable(Solution_Server
        main.cpp
        ClientHandler/ClientHandler.h
        ClientHandler/MyTestClientHandler.cpp
        ClientHandler/MyTestClientHandler.h
        Server/Server.h
        Server/TCPServer.cpp
        Server/TCPServer.h
        Server/MySerialServer.cpp
        Server/MySerialServer.h
        Server/MyParallelServer.cpp
        Server/MyParallelServer.h
        Server/SocketStream.cpp
        Server/SocketStream.h
        Server/InputStream.cpp
        Server/InputStream.h
        Server/OutputStream.cpp
        Server/OutputStream.h
        Solver/Solver.h
        Searcher/StringReverser.cpp
        Searcher/StringReverser.h
        CacheManager/CacheManager.h
        CacheManager/FileCacheManager.cpp
        CacheManager/FileCacheManager.h
        Searcher/State.h
        Searcher/Searchable.h
        Searcher/Searcher.h
        Searcher/BestFirstSearch.h
        Searcher/PriorityQueueSearcher.h
        Searcher/StateCompare.h
        Searcher/BreadthFirstSearch.h
        Searcher/MySearcher.h
        Searcher/DepthFirstSearch.h Searcher/AStar.h)
