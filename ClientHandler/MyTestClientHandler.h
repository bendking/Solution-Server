//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
#define SOLUTION_SERVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "../CacheManager/CacheManager.h"
#include "../Searcher/StringReverser.h"
#include "../Server/InputStream.h"
#include "../Server/OutputStream.h"
#include <string>

#define MY_TEST_CLIENT_FILE_NAME "my_text_file.txt"

using namespace std;

class MyTestClientHandler : ClientHandler{
private:
    Solver<string, string>* solver;
    CacheManager* cacheManager;
public:
    // C_tor
    MyTestClientHandler(Solver<string, string>* _solver, CacheManager* _cacheManager);
    ~MyTestClientHandler();

    // Implement ClientHandler
    void handleClient(InputStream& input, OutputStream& output);
};


#endif //SOLUTION_SERVER_MYTESTCLIENTHANDLER_H
