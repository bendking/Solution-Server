#include "Searcher/StringReverser.h"
#include "CacheManager/FileCacheManager.h"
#include "ClientHandler/MyTestClientHandler.h"
#include "Server/MySerialServer.h"
#include "Server/MyParallelServer.h"
#include <string>
#include <thread>

namespace boot {

    class Main {
    public:
        void test_serial_server()
        {
            StringReverser* stringReverser = new StringReverser();
            FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
            MyTestClientHandler<string, string>* clientHandler = new MyTestClientHandler<string, string>(stringReverser, cacheManager);

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

        void test_parallel_server()
        {
            StringReverser* stringReverser = new StringReverser();
            FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
            MyTestClientHandler<string, string>* clientHandler = new MyTestClientHandler<string, string>(stringReverser, cacheManager);

            // Define server and start it
            MyParallelServer* server = new MyParallelServer(clientHandler);
            server->open(5400);
            server->start();
            /*
             * Run Python code as client (must open new socket for each connection)
             * Python code is in python_test (copy-paste into python3 command-line)
             */
            // Sleep then stop
            std::this_thread::sleep_for(std::chrono::seconds(10));
            server->stop();
            delete server;
        }

        int main () {
            test_parallel_server();
            return 1;
        }
    };
}

using namespace boot;
int main () {
    Main m;
    return m.main();
}