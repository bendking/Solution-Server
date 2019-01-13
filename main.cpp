#include "ClientHandler/TestClientHandler.h"
#include "CacheManager/FileCacheManager.h"
#include "Server/MySerialServer.h"
#include "Server/MyParallelServer.h"
#include "Searcher/StringReverser.h"
#include "Searchable/MatrixSearchable.h"
#include "Searcher/BreadthFirstSearch.h"
#include "Searcher/BestFirstSearch.h"
#include "Searcher/DepthFirstSearch.h"
#include "Searcher/AStar.h"
#include "Tester/SearcherTester.h"

#include <string>
#include <thread>
#include <MyClientHandler.h>

// Use as shorthand
#define MATRIX_PROBLEM Searchable<Cell>*, State<Cell>*

namespace boot
{
    class Main {
    public:
        void test_serial_reverser()
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
            // Delete server (and thus handler)
            delete server;
        }

        void test_parallel_reverser()
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
            delete server;
        }

        void test_searcher()
        {
            SearcherTester tester;
            tester.test();
        }

        void main_test(string server_type)
        {
            // Initialize searcher & solver (decided based on graphs)
            Searcher<Cell>* searcher = new AStar<Cell>();
            Solver<Searchable<Cell>*, State<Cell>*>* solver = new SearcherSolver<Cell>(searcher);

            // Initialize cache manager & client handler
            FileCacheManager* cacheManager = new FileCacheManager("searcher_cache.txt");
            auto clientHandler = new MyClientHandler<Searchable<Cell>*, State<Cell>*>(solver, cacheManager);

            // Define server and start it
            Server* server;

            if (server_type == "serial") {
                server = new MySerialServer(clientHandler);
            }
            // Else
            if (server_type == "parallel") {
                server = new MyParallelServer(clientHandler);
            }
            // Else, fucked

            server->open(5400);
            server->start();
            /*
             * Run Python code as client (must open new socket for each connection)
             * Python code is in python_test (copy-paste into python3 command-line)
             */
            // TODO: Delete all objects
            delete server; // Deletes nested objects
            delete searcher;
        }

        int main () {
            //test_serial_reverser();
            //test_parallel_reverser();
            //test_solver();
            test_searcher();
            main_test("serial");
            return 1;
        }
    };
}

using namespace boot;
int main () {
    Main m;
    return m.main();
}