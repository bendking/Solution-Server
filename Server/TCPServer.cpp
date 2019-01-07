//
// Created by ben on 1/5/19.
//

#include "TCPServer.h"

TCPServer::TCPServer() {
    sock = -1;
    port = 0;
}

bool TCPServer::open(int port, ClientHandler* handler)
{
    this->port = port;
    this->handler = handler;
    return bind();
}

void TCPServer::handle(InputStream *input, OutputStream *output) {
    return handler->handleClient(input, output);
}

bool TCPServer::bind()
{
    // Attempt socket creation if it is not already created
    if (sock == -1) {
        // Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1) {
            perror("Failed to create socket");
            return false;
        }
    }

    // Forcefully attaching socket to the port 8080
    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return false;
    }

    // Set server attributes
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Bind server to socket
    if ((::bind(sock, (struct sockaddr*) &server, sizeof(address))) < 0) {
        perror("Failed to bind TCPServer");
        return false;
    }
    // Else, binding succeeded
    return true;
}

int TCPServer::listen()
{
    int client_limit = 100;
    // Attempt to listen
    if (::listen(sock, client_limit) < 0) {
        perror("listen");
    }

    int addrlen = sizeof(address);
    int new_socket; // Socket with client            BIG BUG
    // Attempt to accept new client                  MEMORIAL
    if ((new_socket = accept(sock, (struct sockaddr *)&server, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
    }

    // Return socket for input
    return new_socket;
}

char* TCPServer::get_buffer() {
    return buffer;
}

int TCPServer::get_read() {
    return read_value;
}

bool& TCPServer::getStop() {
    return stop_flag;
}
