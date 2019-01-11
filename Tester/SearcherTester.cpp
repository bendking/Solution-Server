//
// Created by ben on 1/11/19.
//

#include "SearcherTester.h"


SearcherTester::SearcherTester() {

}

void SearcherTester::run()
{
    StringReverser* stringReverser = new StringReverser();
    FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
    TestClientHandler<string, string>* clientHandler = new TestClientHandler<string, string>(stringReverser, cacheManager);

    // Define server and start it
    MySerialServer* server = new MySerialServer(clientHandler);
    server->open(5400);
    server->start();
    /*
     * Run Python code as client (must open new socket for each connection)
     * Python code is in python_test (copy-paste into python3 command-line)
     */
    // Sleep then stop
    std::this_thread::sleep_for(std::chrono::seconds(5));
    server->stop();
    // Delete server (and handler)
    delete server;
}