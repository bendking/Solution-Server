//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_SERVER_H
#define SOLUTION_SERVER_SERVER_H

#include "../ClientHandler/ClientHandler.h"
#include "InputStream.h"
#include "OutputStream.h"

namespace server_side {
    class Server {
    public:
        // Elementary
        virtual bool open(int port) = 0; // Uses bind & listen
        virtual int start() = 0; // Handle clients
        virtual void stop() = 0; // Stop handling clients
        virtual char* get_buffer() = 0; // Gets buffer
        // Helper
        virtual bool bind() = 0; // Bind to a port
        virtual int listen() = 0; // Listen for a client
    };
}

#endif //SOLUTION_SERVER_SERVER_H
