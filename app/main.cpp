#include "socket/rawsocket.h"
#include "buffer/buffer.h"
#include <netdb.h>
#include <stdlib.h>
#include <iostream>
#include <string_view>


int main(int argc, char* argv[])
{
    struct sockaddr saddr;
    ssize_t saddrLength;
    
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
    Buffer* b = new Buffer(4096);
    ssize_t bsize = recvfrom(desc, b, b->getCapacity(), 0, &saddr, (socklen_t*)&saddrLength);
    socket.closeSocket();

    exit(EXIT_SUCCESS);
}