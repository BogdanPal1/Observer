#include "../include/socket/rawsocket.h"
#include <netdb.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char* argv[])
{
    // Creating raw socket
    RawSocket socket = RawSocket::getInstance();
    int desc = 0;
    desc = socket.getDescriptor();
    if (desc < 0)
    {
        std::cerr << "Can't create socket!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket created with descriptor: " << desc << std::endl;

    socket.closeSocket();

    exit(EXIT_SUCCESS);
}