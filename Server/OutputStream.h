//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_OUTPUTSTREAM_H
#define SOLUTION_SERVER_OUTPUTSTREAM_H

#include "SocketStream.h"
#include <string>
#include <cstring>
#include <sys/socket.h>


using namespace std;

class OutputStream : public SocketStream {
private:
    int socket;
public:
    int send(string buffer);
};


#endif //SOLUTION_SERVER_OUTPUTSTREAM_H
