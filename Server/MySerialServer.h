//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYSERIALSERVER_H
#define SOLUTION_SERVER_MYSERIALSERVER_H

#include <string>
#include "Server.h"


using namespace server_side;
class MySerialServer : public Server {
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
    // Variables for reading
    char buffer[1024] = {0};
    int read_value;
public:
    MySerialServer();
    int open(int port);
    int stop();
    int bind(int port);
    int listen();
    void read();
    char* get_buffer();
};


#endif //SOLUTION_SERVER_MYSERIALSERVER_H
