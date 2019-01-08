//
// Created by ben on 1/8/19.
//

#include "SocketStream.h"

SocketStream::SocketStream() = default;

SocketStream::SocketStream(int _socket) {
    socket = _socket;
}

void SocketStream::setSocket(int _socket) {
    socket = _socket;
}

int SocketStream::getSocket() {
    return socket;
}