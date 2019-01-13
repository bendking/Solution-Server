#include "Searcher/StringReverser.h"
#include "CacheManager/FileCacheManager.h"
#include "TestClientHandler.h"
#include "Server/MySerialServer.h"
#include "Server/MyParallelServer.h"
#include "Searchable/MatrixSearchable.h"
#include "Searcher/BreadthFirstSearch.h"
#include "Searcher/AStar.h"
#include "Tester/SearcherTester.h"

#include "Searcher/DepthFirstSearch.h"
#include "Searcher/BestFirstSearch.h"
#include <string>
#include <thread>
#include <MyClientHandler.h>

namespace boot
{
    class Main {
    public:
        void test_serial_server()
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
            //std::this_thread::sleep_for(std::chrono::seconds(5));
            //server->stop();
            // Delete server (and handler)
            delete server;
        }

        void test_parallel_server()
        {
            StringReverser* stringReverser = new StringReverser();
            FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
            TestClientHandler<string, string>* clientHandler = new TestClientHandler<string, string>(stringReverser, cacheManager);

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

        void test_solver()
        {
            int** a = new int*[3];
            for(int i = 0; i < 4; ++i) {
                a[i] = new int[3];
                a[i][0] = 3;
                a[i][1] = 2;
                a[i][2] = 1;
                a[i][3] = 0;

            }

            MatrixSearchable* sr = new MatrixSearchable(4,4,a);
            AStar<Cell> searcher = AStar<Cell>();
            State<Cell>* state = searcher.search(sr);
        }

        void test_searcher()
        {
            SearcherTester tester;
            tester.test();
        }

        void main_test()
        {
            // Initialize searcher & solver (decided based on graphs)
            Searcher<Cell>* searcher = new AStar<Cell>();
            Solver<Searchable<Cell>*, State<Cell>*>* solver = new SearcherSolver<Cell>(searcher);

            // Initialize cache manager & client handler
            FileCacheManager* cacheManager = new FileCacheManager("searcher_cache.txt");
            auto clientHandler = new MyClientHandler<Searchable<Cell>*, State<Cell>*>(solver, cacheManager);

            // Define server and start it
            MyParallelServer* server = new MyParallelServer(clientHandler);
            server->open(5400);
            server->start();
            /*
             * Run Python code as client (must open new socket for each connection)
             * Python code is in python_test (copy-paste into python3 command-line)
             */
            // Delete all objects
            delete server;
        }

        int main () {
            //test_serial_server();
            //test_parallel_server();
            //test_solver();
            test_searcher();
            //main_test();
            return 1;
        }
    };
}

using namespace boot;
int main () {
    Main m;
    return m.main();
}