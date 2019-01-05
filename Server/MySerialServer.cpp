//
// Created by ben on 1/4/19.
//

#include "MySerialServer.h"

MySerialServer::MySerialServer() : TCPServer() { }

MySerialServer::~MySerialServer()
{
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

    bool stop = server->getStop();
    while (!stop)
    {
        // Get new client
        int new_socket = server->listen();
        // Set client socket to streams
        input->setSocket(new_socket);
        output->setSocket(new_socket);
        // Give streams to handler
        server->handle(input, output);
    }

    delete input;
    delete output;
}

//
// Server functions
//

// Listen & handle client in succession
bool MySerialServer::start()
{
    thread = new pthread_t;
    pthread_create(thread, nullptr, loop, this);
}

void MySerialServer::stop() {
    stop_flag = true;
}

void MySerialServer::read(int sock) {
    memset(buffer, 0, sizeof(buffer));
    read_value = ::read(sock, buffer, 1024);
}

/* OLD CLOSE
void MySerialServer::stop_server()
 {
    shutdown(sock, SHUT_WR);
    close(sock);
}
*/