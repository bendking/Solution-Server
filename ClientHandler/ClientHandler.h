//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_CLIENTHANDLER_H
#define SOLUTION_SERVER_CLIENTHANDLER_H

#include "../Server/InputStream.h"
#include "../Server/OutputStream.h"

using namespace std;

class ClientHandler {
public:
    // Accepts abstract streams with client
    virtual void handleClient(InputStream *input, OutputStream *output) = 0;
    virtual ~ClientHandler() = default;

    // Clone method: stateless - should return self, stateful - should return a clone of self
    virtual ClientHandler* clone() = 0;
};

#endif //SOLUTION_SERVER_CLIENTHANDLER_H
