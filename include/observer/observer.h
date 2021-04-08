#ifndef OBSERVER_H
#define OBSERVER_H

#include <getopt.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <memory>

#include "exceptions/exceptions.h"
#include "socket/socket.h"

/**
 * @brief Main class
 * 
 * @details This class contains main methods of program 
 */
class Observer
{
public:
    static Observer& getObserver()
    {
        static Observer instance;
        return instance;
    }

    ~Observer();

    void init(int argc, char *argv[]);
    void cleanup();
private:
    Observer();
    Observer(const Observer& other) = default;
    Observer& operator=(const Observer& other) = default;
    Observer(const Observer&& other) = delete;
    Observer& operator=(const Observer&& other) = delete;

    void listDevicesAndExit();
    unsigned int getDeviceIndex(const std::string& name) const;
    int getProtocolByName(const std::string& name) const;
    void openInterface();
    std::string getOption(char* option);

private:
    enum class Protocols
    {
        IPv4 = ETH_P_IP,
        IPv6 = ETH_P_IPV6,
        ARP = ETH_P_ARP,
    };

private:
    std::string _device;
    std::unique_ptr<char[]> _buffer;
    int _protocol;
    int _sockd;
    std::unique_ptr<Socket> _socket;
};

#endif // OBSERVER_H
