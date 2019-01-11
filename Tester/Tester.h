//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_TESTER_H
#define SOLUTION_SERVER_TESTER_H

#include "../ClientHandler/TestClientHandler.h"
#include "../ClientHandler/MyClientHandler.h"
#include "../Server/MySerialServer.h"
#include "../Server/MyParallelServer.h"
#include "../Searcher/StringReverser.h"
#include "../CacheManager/FileCacheManager.h"
#include <thread>

class Tester {
public:
    Tester();
    void run(TCPServer* server);
    void run_serial();
    void run_parallel();
};


#endif //SOLUTION_SERVER_TESTER_H
