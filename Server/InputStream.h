//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_INPUTSTREAM_H
#define SOLUTION_SERVER_INPUTSTREAM_H


#include <string>
#include <cstring>
#include <unistd.h>

class InputStream {
private:
    int socket;
    char buffer[1024] = {0};
public:
    InputStream();
    void setSocket(int _socket);
    std::string read();
};


#endif //SOLUTION_SERVER_INPUTSTREAM_H
