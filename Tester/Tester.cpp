//
// Created by ben on 1/11/19.
//

#include "Tester.h"

Tester::Tester() {

}

void Tester::run(TCPServer* server)
{
    StringReverser* stringReverser = new StringReverser();
    FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
    TestClientHandler<string, string>* clientHandler = new TestClientHandler<string, string>(stringReverser, cacheManager);

    // Define server and start it
    server->setClientHandler(clientHandler);
    server->open(5400);
    server->start();
    /*
     * Run Python code as client (must open new socket for each connection)
     * Python code is in python_test (copy-paste into python3 command-line)
     */
    // Sleep then stop
    std::this_thread::sleep_for(std::chrono::seconds(10));
    server->stop();
    // Delete server (and handler)
    delete server;
}


void Tester::run_serial()
{
    MySerialServer* server = new MySerialServer();
    run(server);
}

void Tester::run_parallel()
{
    MyParallelServer* server = new MyParallelServer();
    run(server);
}