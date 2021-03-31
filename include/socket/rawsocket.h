#ifndef RAW_SOCKET_H
#define RAW_SOCKET_H

#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

class RawSocket
{
public:
    static RawSocket &getInstance()
    {
        static RawSocket _instance;
        return _instance;
    }
    int getDescriptor() const;
    void closeSocket();
    ~RawSocket();

protected:
    RawSocket();

private:
    int _sockd = 0;
};

#endif // RAW_SOCKET_H