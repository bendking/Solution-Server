//
// Created by ben on 1/4/19.
//

#include "OutputStream.h"


OutputStream::OutputStream() {

}

void OutputStream::setSocket(int _socket) {
    socket = _socket;
}

bool OutputStream::send(string data) {
    // Send a message
    if (::send(socket, data.c_str(), strlen(data.c_str()), 0) < 0) {
        perror("Failed to send message");
        return false;
    }
    // Else
    return true;
}