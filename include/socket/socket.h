#ifndef OBSERVER_SOCKET_H
#define OBSERVER_SOCKET_H

#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief The Socket class
 * 
 */
class Socket
{
public:
    /**
     * @brief The Type enum - stores types of sockets, which we can use
     * 
     */
    enum class Type
    {
        DGRAM = SOCK_DGRAM,
        RAW = SOCK_RAW,
    };

public:
    /**
    * @brief Construct a new Socket object
    * 
    */
    Socket();
    
    /**
     * @brief Construct a new Socket object
     * 
     * @param type The type of socket
     * @param protocol The protocol
     */
    Socket(Type type, int protocol);

    /**
     * @brief Get the Descriptor object
     * 
     * @return int Descriptor of socket
     */
    int getDescriptor() const;

    /**
     * @brief Close socket
     * 
     */
    void closeSocket();

    /**
     * @brief Destroy the Socket object
     * 
     */
    ~Socket();

private:
    int _sockd = 0;
};

#endif // OBSERVER_SOCKET_H