#ifndef OBSERVER_SOCKET_H
#define OBSERVER_SOCKET_H

#include <sys/socket.h>
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
        RAW   = SOCK_RAW,
    };

    enum class Domain
    {
        INET   = AF_INET,
        PACKET = AF_PACKET,
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
    Socket(Domain domain, Type type, int protocol);

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
    int _sockd = -1;
};

#endif // OBSERVER_SOCKET_H