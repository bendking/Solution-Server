//
// Created by ben on 1/4/19.
//

#include "OutputStream.h"


int OutputStream::send(string data) {
    // Send a message
    int result = ::send(socket, data.c_str(), strlen(data.c_str()), 0);
    if (result < 0) {
        perror("Failed to send message");
    }
    // Else
    return result;
}