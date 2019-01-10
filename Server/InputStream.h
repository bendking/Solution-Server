//
// Created by ben on 1/4/19.
//

#ifndef SOLUTION_SERVER_INPUTSTREAM_H
#define SOLUTION_SERVER_INPUTSTREAM_H

#include "SocketStream.h"
#include <string>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

class InputStream : public SocketStream {
private:
    pthread_mutex_t* mutex = NULL;
    char buffer[1024] = {0};
public:
    void setMutex(pthread_mutex_t* _mutex);
    std::string read();
};


#endif //SOLUTION_SERVER_INPUTSTREAM_H
