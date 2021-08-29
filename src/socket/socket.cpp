#include "socket/socket.h"

Socket::Socket()
{
    _sockd = socket(static_cast<int>(Domain::PACKET), static_cast<int>(Type::DGRAM), 0);
}

Socket::Socket(Domain domain, Type type, int protocol)
{
    _sockd = socket(static_cast<int>(domain), static_cast<int>(type), protocol);
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
