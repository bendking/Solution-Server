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
#include "Solver/SearcherSolver.h"
#include "Tester/SearcherTester.h"
#include "ClientHandler/MyClientHandler.h"

#include <string>
#include <thread>

// Use as shorthand
#define MATRIX_PROBLEM Searchable<Cell>*, State<Cell>*

namespace boot
{
    class Main {
    public:
        void test_searcher()
        {
            SearcherTester tester;
            tester.test();
        }

        void main_test(string server_type, int port)
        {
            // Initialize searcher & solver (decided based on graphs)
            Searcher<Cell>* searcher = new BestFirstSearch<Cell>();
            Solver<MATRIX_PROBLEM>* solver = new SearcherSolver<Cell>(searcher);

            // Initialize cache manager & client handler
            FileCacheManager* cacheManager = new FileCacheManager("searcher_cache.txt");
            auto clientHandler = new MyClientHandler<MATRIX_PROBLEM>(solver, cacheManager);

            // Define server and start it
            Server* server;

            // Sort out server type
            if (server_type == "serial")
            {
                server = new MySerialServer(clientHandler);
            }
            else if (server_type == "parallel")
            {
                server = new MyParallelServer(clientHandler);
            }
            else // If no type supplied
            {
                throw logic_error("No server type supplied, dickhead");
            }
            // Else, fucked

            server->open(port);
            server->start();
            /*
             * Run Python code as client (must open new socket for each connection)
             * Python code is in test_parallel or test_serial (copy-paste into python3 command-line)
             */
            delete server; // Deletes nested objects
            delete cacheManager; // Save to file
        }

        int main (int port) {
            //test_serial_reverser();
            //test_parallel_reverser();
            //test_solver();
            //test_searcher();
            main_test("parallel", port);
            return 1;
        }
    };
}

using namespace boot;
int main (int argc, char *argv[]) {
    Main menu;
    return menu.main(stoi(argv[1]));
    //Debug:
    //return menu.main(5400);
}