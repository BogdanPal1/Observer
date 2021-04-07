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

#include "exceptions/exceptions.h"

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
    unsigned int getDeviceIndex(char *name) const;
    int getProtocolByName(char *name) const;
    void openInterface();
    char* getOption(char* option);

private:
    enum class Protocols
    {
        IPv4 = ETH_P_IP,
        IPv6 = ETH_P_IPV6,
        ARP = ETH_P_ARP,
    };

private:
    char *_device;
    char*_buffer;
    int _protocol;
    int _sockd;
};

#endif // OBSERVER_H
