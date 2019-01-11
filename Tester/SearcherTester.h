//
// Created by ben on 1/11/19.
//

#ifndef SOLUTION_SERVER_SEARCHERTEST_H
#define SOLUTION_SERVER_SEARCHERTEST_H

#include "../ClientHandler/TestClientHandler.h"
#include "../ClientHandler/MyClientHandler.h"
#include "../Server/MySerialServer.h"
#include "../Server/MyParallelServer.h"
#include "../Searcher/StringReverser.h"
#include "../CacheManager/FileCacheManager.h"
#include <thread>

class SearcherTester {
    SearcherTester();
    void run();
};


#endif //SOLUTION_SERVER_SEARCHERTEST_H
