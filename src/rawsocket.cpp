#include "../include/rawsocket.h"

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
    close(_sockd);
    _sockd = 0;
}

void analyzer::RawSocket::closeSocket()
{
    close(_sockd);
    _sockd = 0;
}
