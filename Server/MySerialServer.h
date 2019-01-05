//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYSERIALSERVER_H
#define SOLUTION_SERVER_MYSERIALSERVER_H

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

using namespace server_side;
class MySerialServer : public Server {
private:
    ClientHandler* handler;
    struct sockaddr_in server;
    std::string address;
    // Thread
    pthread_t* thread = NULL;
    bool stop = false;
    // Config
    int port;
    int sock;
    // Variables for reading
    char buffer[1024] = {0};
    int read_value;
public:
    // Elementary
    MySerialServer();
    ~MySerialServer();
    bool open(int port, ClientHandler* handler);
    bool start();
    void stop();
    void handle(InputStream* input,OutputStream* output);
    // Helpers
    bool bind();
    int listen();
    void read(int sock);
    char* get_buffer();
    int get_read();
    // Get methods
    bool& getStop();
};


#endif //SOLUTION_SERVER_MYSERIALSERVER_H
