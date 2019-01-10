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

/* Blocking listen
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
    if ((new_socket = accept(sock, (struct sockaddr*) &server, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
    }

    // Return socket for input
    return new_socket;
}
*/

// Non-blocking listen
int TCPServer::listen()
{
    // Set socket to non-blocking
    set_blocking(sock, 0);

    // Server info //
    int addrlen = sizeof(address);
    int client_limit = 100;
    int new_socket = -1;

    // Timeout info //
    int time_limit = 5;
    struct timeval timeout;
    fd_set fd;
    int retval;
    int max = sock + 1;

    // Attempt to get client
    bool stop = this->getStop();
    while (!stop)
    {
        // Attempt to listen
        if (::listen(sock, client_limit) < 0) {
            perror("listen");
        }

        // Define timout
        timeout.tv_sec = time_limit;
        timeout.tv_usec = 0;

        // Track fd
        FD_ZERO(&fd);
        FD_SET(sock, &fd);

        // Check if socket is ready
        retval = ::select(max, &fd, NULL, NULL, &timeout);

        // If there was an incoming request to master socket
        if (FD_ISSET(sock, &fd))
        {
            // Attempt to accept new client              BIG BUG MEMORIAL
            if ((new_socket = accept(sock, (struct sockaddr*) &server, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
            }

            // Set socket to blocking
            set_blocking(sock, 1);
            return new_socket;
        }

        // If timed out, loop again
        if (retval == 0) {
            stop = this->getStop();
            continue;
        }

        // If an error has occurred
        if (retval == -1) {
            set_blocking(sock, 1);
            perror("select()");
        }
    }

    // Set socket to blocking
    set_blocking(sock, 1);
    return new_socket;
}

bool TCPServer::set_blocking(const int &socket, bool should_block)
{
    // Whether the operation succeeded
    bool ret = true;

    // Get flags and check if set is redundant
    const int flags = fcntl(socket, F_GETFL, 0);
    if ((flags & O_NONBLOCK) && !should_block) { return ret; }
    if (!(flags & O_NONBLOCK) && should_block) { return ret; }
    // If set isn't redundant, set as specified
    ret = 0 == fcntl(socket, F_SETFL, should_block ? flags ^ O_NONBLOCK : flags | O_NONBLOCK);

    // If a set was made, return true
    return ret;
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
