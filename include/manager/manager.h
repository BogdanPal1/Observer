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
#include "buffer/buffer.h"
#include "parser/parser.h"

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
    int getEthernetProtoByName(const std::string& name) const;
    int getInternetProtoByName(const std::string& name) const;
    void openInterface();
    std::string getOption(char* option);

private:
    /**
     * @brief The Ethernet Protocols enumeration
     * 
     * 
     */
    enum class EProtocols
    {
        IPv4 = ETH_P_IP,
        IPv6 = ETH_P_IPV6,
        ARP = ETH_P_ARP,
        ALL = ETH_P_ALL,
    };

    /**
     * @brief The Internet Protocols enumeration
     *
     *
     */
    enum class IProtocols
    {
        IP = 0,
        TCP = 6,
        UDP = 17,
    };

private:
    std::string _device;
    std::string _outputFile;
    int _eProtocol;
    int _iProtocol;
    int _sockd;
    std::unique_ptr<Socket> _socket;
    std::unique_ptr<Parser> _parser;
};

#endif // MANAGER_H
