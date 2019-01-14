//
// Created by ben on 1/5/19.
//

#ifndef SOLUTION_SERVER_MYPARALLELSERVER_H
#define SOLUTION_SERVER_MYPARALLELSERVER_H


#include <vector>
#include "TCPServer.h"

using namespace server_side;

class MyParallelServer : public TCPServer {
private:
    pthread_mutex_t* mutex = NULL;
    vector<pthread_t*> threads;
public:
    // Override
    virtual ~MyParallelServer() override;  // Delete handler & thread
    int start() override;        // Start handle loop
    void stop() override;         // Stop handle loop
    void read(int sock) override;          // Read from client

    // Elementary
    MyParallelServer();
    MyParallelServer(ClientHandler* clientHandler);
    pthread_mutex_t* getMutex();
    void addThread(pthread_t* pthread);
    void deleteThreads();
};


#endif //SOLUTION_SERVER_MYPARALLELSERVER_H
