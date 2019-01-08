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
        int main () {
            StringReverser* stringReverser = new StringReverser();
            FileCacheManager* cacheManager = new FileCacheManager("test_file.txt");
            MyTestClientHandler<string, string>* clientHandler = new MyTestClientHandler<string, string>(stringReverser, cacheManager);

            // Define server and start it
            MySerialServer server(clientHandler);
            server.open(5400);
            server.start();
            /*
             * Run Python code as client (must open new socket for each connection)
             * Python code in different file
             */
            // Sleep then stop
            std::this_thread::sleep_for(std::chrono::seconds(60));
            server.stop();
            return 1;
        }
    };
}

using namespace boot;
int main () {
    Main m;
    return m.main();
}