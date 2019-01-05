#include "Searcher/StringReverser.h"
#include "CacheManager/FileCacheManager.h"
#include "ClientHandler/MyTestClientHandler.h"

#include <string>
namespace boot {
    class Main {

    public:
        int main () {
            StringReverser sr;
            FileCacheManager fcm("test_file.txt");
            MyTestClientHandler<string, string> myTestClientHandler(&sr, &fcm);

            // need to inject it to server
            // be careful that sr and fcm will not be deleted!
            return 1;
        }
    };
}

using namespace boot;
int main () {
    Main m;
    return m.main();
}