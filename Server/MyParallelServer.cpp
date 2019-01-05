//
// Created by ben on 1/5/19.
//

#include "MyParallelServer.h"

MyParallelServer::MyParallelServer() : TCPServer() {
    mutex = new pthread_mutex_t;
}

MyParallelServer::~MyParallelServer()
{
    // In case stop wasn't activated
    stop();

    // Wait for threads
    char* dummy;
    for (pthread_t* thread : threads) {
        pthread_join(*thread, (void**)dummy);
    }

    deleteThreads();
    delete mutex;

    // Delete ClientHandler
    if (handler != NULL) {
        delete handler;
    }
}

//
// Thread functions
//

struct arg_struct {
    MyParallelServer* server;
    InputStream* input;
    OutputStream* output;
};

/*
 * Thread in charge of handling the client
 * and deleting their relevant allocated types
 */
void* handle_client(void* _args)
{
    // Get arguments needed
    arg_struct* args = (arg_struct*) _args;
    MyParallelServer* server = args->server;
    InputStream* input = args->input;
    OutputStream* output = args->output;

    // Handle client
    server->handle(input, output);

    delete input;
    delete output;
    delete args;
}


/*
 * Thread in charge of listening for clients
 * and opening new threads for them the be handled in
 */
void* get_clients(void* args)
{
    MyParallelServer* server = (MyParallelServer*) args;
    bool stop = server->getStop();

    vector<arg_struct*> structs;
    while (!stop)
    {
        // Get new client
        int new_socket = server->listen();

        // Make input & output streams
        InputStream* input = new InputStream;
        OutputStream* output = new OutputStream;
        // Set client socket to streams
        input->setSocket(new_socket);
        input->setMutex(server->getMutex());
        output->setSocket(new_socket);


        // Initialize arg_struct
        auto args = new struct arg_struct;
        args->server = server;
        args->input = input;
        args->output = output;
        // Put args point to vector
        structs.push_back(args);

        // Initialize new thread
        pthread_t* pthread = new pthread_t;
        server->addThread(pthread);
        pthread_create(pthread, nullptr, handle_client, args);
    }
}

pthread_mutex_t* MyParallelServer::getMutex() {
    return mutex;
}

void MyParallelServer::addThread(pthread_t* pthread) {
    threads.push_back(pthread);
}


void MyParallelServer::deleteThreads()
{
    for (pthread_t* thread : threads) {
        delete thread;
    }
}

//
// Server functions
//

// Listen & handle client in succession
bool MyParallelServer::start()
{
    pthread_t* thread = new pthread_t;
    threads.push_back(thread );
    pthread_create(thread, nullptr, get_clients, this);
}

void MyParallelServer::stop(){
    stop_flag = true;
}

void MyParallelServer::read(int sock)
{
    memset(buffer, 0, sizeof(buffer));
    read_value = ::read(sock, buffer, 1024);
}