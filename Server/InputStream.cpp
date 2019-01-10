//
// Created by ben on 1/4/19.
//

#include "InputStream.h"

using namespace std;



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
    ::read(socket, buffer, 1024);

    // If no mutex, simply return buffer
    if (mutex == NULL) {
        return buffer;
    }

    // Else, get copy of buffer
    string _buffer = buffer;

    // If mutex in place, unlock
    if (mutex != NULL) {
        pthread_mutex_unlock(mutex);
    }

    return _buffer;
}