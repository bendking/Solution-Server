//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_CLIENTHANDLER_H
#define SOLUTION_SERVER_CLIENTHANDLER_H

#include "../Server/InputStream.h"
#include "../Server/OutputStream.h"

using namespace std;
class ClientHandler {
private:

public:
    // Accepts abstract stream and handles it
    virtual void handleClient(InputStream *input, OutputStream *output) = 0;
};

#endif //SOLUTION_SERVER_CLIENTHANDLER_H
