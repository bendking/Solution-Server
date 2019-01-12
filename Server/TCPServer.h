//
// Created by ben on 1/5/19.
//

#ifndef SOLUTION_SERVER_TCPSERVER_H
#define SOLUTION_SERVER_TCPSERVER_H

#include "Server.h"

#include <iostream>	// cout
#include <stdio.h>	// printf
#include <string.h>	// strlen
#include <string>	// string
#include <sys/socket.h>	// socket
#include <arpa/inet.h>	// inet_addr
#include <netdb.h>	// hostent
#include <unistd.h> // read
#include <pthread.h> // thread
#include <fcntl.h>

using namespace server_side;

class TCPServer : public Server {
protected:
    // Objects
    ClientHandler* handler = NULL;
    struct sockaddr_in server;
    std::string address;
    // Thread
    bool stop_flag = false;
    // Config
    int port;
    int sock;
    // Variables for reading
    char buffer[1024] = {0};
    int read_value;
public:
    // Virtual
    TCPServer(ClientHandler* clientHandler);
    virtual ~TCPServer() = default;
    virtual bool start() = 0;        // Start handle loop
    virtual void stop() = 0;         // Stop handle loop
    virtual void read(int sock) = 0; // Read from client
    // Elementary
    TCPServer();

    bool open(int port) override;
    void handleClient(InputStream* input,OutputStream* output);

    // Helpers
    void setClientHandler(ClientHandler* clientHandler);
    bool bind() override;         // Bind to port supplied
    int listen() override;        // Listen for a client
    int timeout_listen();         // Listen for a client with a timeout
    bool set_blocking(const int &socket, bool should_block);
    void closeSocket(int socket); // Shutdown and close
    char* get_buffer() override;  // Get what was read
    int get_read();               // Return read value
    bool& getStop();              // Flag for start()
};


#endif //SOLUTION_SERVER_TCPSERVER_H
