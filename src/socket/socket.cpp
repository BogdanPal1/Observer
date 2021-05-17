#include "socket/socket.h"

Socket::Socket()
{
    _sockd = socket(AF_PACKET, static_cast<int>(Type::DGRAM), 0);
}

Socket::Socket(Type type, int protocol)
{
    _sockd = socket(AF_PACKET, static_cast<int>(type), protocol);
}

int Socket::getDescriptor() const
{
    return _sockd;
}

Socket::~Socket()
{
    closeSocket();
}

void Socket::closeSocket()
{
    if (_sockd >= 0)
    {
        close(_sockd);
    }
}
