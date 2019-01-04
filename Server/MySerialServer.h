//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYSERIALSERVER_H
#define SOLUTION_SERVER_MYSERIALSERVER_H

#include "Server.h"

#include <string>
#include <bits/socket.h>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>


using namespace server_side;
class MySerialServer : public Server {
private:
    ClientHandler* handler;
    struct sockaddr_in server;
    std::string address;
    int port;
    int sock;
    // Variables for reading
    char buffer[1024] = {0};
    int read_value;
public:
    // Elementary
    MySerialServer();
    bool open(int port, ClientHandler* handler);
    bool start();
    void stop();
    // Helpers
    bool bind();
    int listen();
    void read(int sock);
    char* get_buffer();
};


#endif //SOLUTION_SERVER_MYSERIALSERVER_H
