//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_MYSERIALSERVER_H
#define SOLUTION_SERVER_MYSERIALSERVER_H


#include "TCPServer.h"

using namespace server_side;

class MySerialServer : public TCPServer {
private:
    pthread_t* thread;
public:
    // Override
    virtual ~MySerialServer() override;   // Delete handler & thread
    int start() override;        // Start handle loop
    void stop() override;         // Stop handle loop
    void read(int sock) override;          // Read from client

    // Elementary
    MySerialServer();
    explicit MySerialServer(ClientHandler* clientHandler);
};


#endif //SOLUTION_SERVER_MYSERIALSERVER_H
