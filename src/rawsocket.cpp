#include "../include/socket/rawsocket.h"

analyzer::RawSocket::RawSocket()
{
    _sockd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
}

int analyzer::RawSocket::getDescriptor() const
{
    return _sockd;
}

analyzer::RawSocket::~RawSocket()
{
    closeSocket();
}

void analyzer::RawSocket::closeSocket()
{
    close(_sockd);
    _sockd = 0;
}
