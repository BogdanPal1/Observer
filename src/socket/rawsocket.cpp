#include "socket/rawsocket.h"

RawSocket::RawSocket()
{
    _sockd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
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
