//;
// Created by ben on 1/4/19.
//

#include "MySerialServer.h"

MySerialServer::MySerialServer() : TCPServer() { }

MySerialServer::MySerialServer(ClientHandler* clientHandler) : TCPServer(clientHandler) { }

MySerialServer::~MySerialServer()
{
    // Wait for thread
    char dummy;
    pthread_join(*thread, (void**) dummy);

    // Delete pthread_t
    if (thread != NULL) {
        delete thread;
    }
    // Delete ClientHandler
    if (handler != NULL) {
        delete handler;
    }
}

//
// Thread functions
//

void* loop(void* args)
{
    MySerialServer* server = (MySerialServer*) args;
    InputStream* input = new InputStream;
    OutputStream* output = new OutputStream;
    int new_socket; // Socket to be used for client

    // Listen once without timeout
    bool stop = server->getStop();
    if (!stop)
    {
        // Get new client
        new_socket = server->listen();
        // Set client socket to streams
        input->setSocket(new_socket);
        output->setSocket(new_socket);
        // Give streams to handler
        server->handleClient(input, output);
        server->closeSocket(new_socket);
    }

    // Listen with timeout
    stop = server->getStop();
    while (!stop)
    {
        // Get new client
        new_socket = server->timeout_listen();
        // If timed-out, continue (stop is true already)
        if (new_socket == -1) {
            stop = server->getStop();
            continue;
        }
        // Else, continue as usual
        // Set client socket to streams
        input->setSocket(new_socket);
        output->setSocket(new_socket);
        // Give streams to handler
        server->handleClient(input, output);
        server->closeSocket(new_socket);
        // Check if should continue
        stop = server->getStop();
    }

    delete input;
    delete output;

    // Junk
    return nullptr;
}

//
// Server functions
//

// Listen & handle client in succession
int MySerialServer::start()
{
    thread = new pthread_t;
    return pthread_create(thread, nullptr, loop, this);
}

void MySerialServer::stop() {
    stop_flag = true;
}

void MySerialServer::read(int sock) {
    memset(buffer, 0, sizeof(buffer));
    read_value = ::read(sock, buffer, 1024);
}