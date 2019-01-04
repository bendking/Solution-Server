//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_SERVER_H
#define SOLUTION_SERVER_SERVER_H

#include "../ClientHandler/ClientHandler.h"

namespace server_side {
    class Server {
        // Elementary
        virtual int open(int port, ClientHandler handler) = 0; // Uses bind & listen
        virtual int stop() = 0; // Stops server
        virtual char* get_buffer() = 0; // Gets buffer
        // Helper
        virtual bool bind(int port) = 0; // Binds to a port
        virtual int listen() = 0; // Listens for clients
    };
}

#endif //SOLUTION_SERVER_SERVER_H
