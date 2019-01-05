//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
#define SOLUTION_SERVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/StringReverser.h"
#include <string>

using namespace std;

class MyTestClientHandler : ClientHandler{
private:
    StringReverser* solver;
    CacheManager* cacheManager;
public:
    void handleClient(istream input, ostream output);
};


#endif //SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
