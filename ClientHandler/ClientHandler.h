//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_CLIENTHANDLER_H
#define SOLUTION_SERVER_CLIENTHANDLER_H

#include <iostream>

using namespace std;
class ClientHandler {
    virtual void handleClient(istream input, ostream output) = 0;
};

#endif //SOLUTION_SERVER_CLIENTHANDLER_H
