#ifndef MANAGER_H
#define MANAGER_H

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
 * @brief The Observer class 
 * Main class of the program
 * 
 * @details This class contains main methods of program 
 */
class Manager
{
public:
    static Manager& getManager()
    {
        static Manager instance;
        return instance;
    }

    ~Manager();

    void init(int argc, char *argv[]);
    void start();
    void cleanup();

private:
    Manager();
    Manager(const Manager& other) = delete;
    Manager& operator=(const Manager& other) = delete;
    Manager(const Manager&& other) = delete;
    Manager& operator=(const Manager&& other) = delete;

    [[ noreturn ]] void listDevicesAndExit();
    [[ noreturn ]] void printHelpAndExit();
    unsigned int getDeviceIndex(const std::string& name) const;
    int getProtocolByName(const std::string& name) const;
    void openInterface();
    std::string getOption(char* option);

private:
    /**
     * @brief The Protocols enumeration
     * 
     * 
     */
    enum class Protocols
    {
        IPv4 = ETH_P_IP,
        IPv6 = ETH_P_IPV6,
        ARP = ETH_P_ARP,
        ALL = ETH_P_ALL,
    };

private:
    std::string _device;
    int _protocol;
    int _sockd;
    std::unique_ptr<Socket> _socket;
};

#endif // MANAGER_H
