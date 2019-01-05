//
// Created by ben on 1/4/19.
//

#include "InputStream.h"

using namespace std;

InputStream::InputStream() {

}

void InputStream::setSocket(int _socket) {
    socket = _socket;
}

void InputStream::setMutex(pthread_mutex_t* _mutex) {
    mutex = _mutex;
}

string InputStream::read() {
    // If mutex in place, lock
    if (mutex != NULL) {
        pthread_mutex_lock(mutex);
    }

    // Reset buffer
    memset(buffer, 0, sizeof(buffer));

    // Read until a line has been input
    while (strlen(buffer) == 0) {
        ::read(socket, buffer, 1024);
    }

    // Get copy of buffer (for multi-threading)
    string _buffer = buffer;

    // If mutex in place, unlock
    if (mutex != NULL) {
        pthread_mutex_lock(mutex);
    }

    return _buffer;
}