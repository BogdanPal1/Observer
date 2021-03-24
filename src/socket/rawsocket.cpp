#include "socket/rawsocket.h"

RawSocket::RawSocket()
{
    _sockd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
}

int RawSocket::getDescriptor() const
{
    return _sockd;
}

RawSocket::~RawSocket()
{
    closeSocket();
}

void RawSocket::closeSocket()
{
    close(_sockd);
    _sockd = 0;
}
