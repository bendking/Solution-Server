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

string InputStream::read() {
    memset(buffer, 0, sizeof(buffer));
    ::read(socket, buffer, 1024);
    return buffer;
}