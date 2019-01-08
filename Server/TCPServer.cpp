//
// Created by ben on 1/5/19.
//

#include "TCPServer.h"

TCPServer::TCPServer() {
    sock = -1;
    port = 0;
}

bool TCPServer::open(int port)
{
    this->port = port;
    return bind();
}

void TCPServer::handleClient(InputStream *input, OutputStream *output) {
    handler->handleClient(input, output);
}

bool TCPServer::bind()
{
    // Attempt socket creation if it is not already created
    if (sock == -1) {
        // Create socket (non-blocking)
        sock = socket(AF_INET , SOCK_STREAM | SOCK_NONBLOCK , 0);
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

    // TIMEOUT
    // Timeout limit (in seconds)
    int time_limit = 60;

    struct timeval timeout;
    fd_set fd;
    int retval;

    // Define timout
    timeout.tv_sec = time_limit;
    timeout.tv_usec = 0;

    // Track fd
    FD_ZERO(&fd);
    FD_SET(0, &fd);

    // Check if socket is ready
    retval = ::select(1, &fd, NULL, NULL, &timeout);

    // If error has occured
    if (retval == -1) {
        perror("select()");
    }
    // If no client has connected within 60 seconds
    if (retval == 0) {
        throw logic_error("Server timed out");
    }

    int addrlen = sizeof(address);
    int new_socket; // Socket with client            BIG BUG
    // Attempt to accept new client                  MEMORIAL
    if ((new_socket = accept(sock, (struct sockaddr*) &server, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
    }

    // Return socket for input
    return new_socket;
}

void TCPServer::closeSocket(int socket) {
    shutdown(socket, SHUT_WR);
    close(socket);
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
