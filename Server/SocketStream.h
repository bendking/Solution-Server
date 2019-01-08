//
// Created by ben on 1/8/19.
//

#ifndef SOLUTION_SERVER_SOCKETSTREAM_H
#define SOLUTION_SERVER_SOCKETSTREAM_H


class SocketStream {
private:
    int socket;
public:
    SocketStream();
    SocketStream(int _socket);
    void setSocket(int _socket);
    int getSocket();
};


#endif //SOLUTION_SERVER_SOCKETSTREAM_H
