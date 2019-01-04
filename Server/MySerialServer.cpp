//
// Created by ben on 1/4/19.
//

#include "MySerialServer.h"

MySerialServer::MySerialServer() {
    sock = -1;
    port = 0;
}

bool MySerialServer::open(int port, ClientHandler* handler)
{
    this->port = port;
    this->handler = handler;
    return bind();
}

bool MySerialServer::bind()
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

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if ((::bind(sock, (struct sockaddr *)&server, sizeof(address))) < 0) {
        perror("Failed to bind MySerialServer");
        return false;
    }
    // Else, binding succeeded
    return true;
}

int MySerialServer::listen()
{
    // Attempt to listen
    if (::listen(sock, 3) < 0) {
        perror("listen");
    }

    int addrlen = sizeof(address);
    int new_socket; // Socket to be returned         BIG BUG
    // Attempt to accept new client                  MEMORIAL
    if ((new_socket = accept(sock, (struct sockaddr *)&server, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
    }
    // Return socket for input
    return new_socket;
}

void MySerialServer::read(int sock) {
    memset(buffer, 0, sizeof(buffer));
    read_value = ::read(sock, buffer, 1024);
}

char* MySerialServer::get_buffer() {
    return buffer;
}

int MySerialServer::get_read_value() {
    return read_value;
}

// Close connection
void MySerialServer::stop() {
    shutdown(sock, SHUT_WR);
    close(sock);
}