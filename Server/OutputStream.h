//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_OUTPUTSTREAM_H
#define SOLUTION_SERVER_OUTPUTSTREAM_H

#include <string>
#include <cstring>
#include <sys/socket.h>


using namespace std;

class OutputStream {
private:
    int socket;
public:
    OutputStream();
    void setSocket(int _socket);
    bool send(string buffer);
};


#endif //SOLUTION_SERVER_OUTPUTSTREAM_H
