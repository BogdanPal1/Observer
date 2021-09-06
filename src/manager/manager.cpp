#include "manager/manager.h"

Manager::Manager() : _device(""), _outputFile(""), _protocol(0), _sockd(-1), _socket(nullptr)
{
}

Manager::~Manager()
{
}

void Manager::init(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "p:d:f:lh")) != -1)
    {
        switch (opt)
        {
        case 'l':
            listDevicesAndExit();
        case 'd':
            _device = getOption(optarg);
            break;
        case 'p':
            _protocol = getProtocolByName(getOption(optarg));
            break;
        case 'f':
            _outputFile = getOption(optarg);
            break;
        case 'h':
            printHelpAndExit();
        case '?':
            std::cout << "Unknown option: " << optopt << std::endl;
            break;
        }
    }
}

void Manager::start()
{
    openInterface();
}

void Manager::cleanup()
{
    if (_socket->getDescriptor() >= 0)
    {
        _socket->closeSocket();
        std::cout << "Socket closed" << std::endl;
    }
}

void Manager::listDevicesAndExit()
{
    struct if_nameindex *nameIndex, *i;
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));

    nameIndex = if_nameindex();
    if (nameIndex == nullptr)
    {
        free(&ifr);
        std::cerr << "ERROR: if_nameindex() return null pointer" << std::endl;
        exit(EXIT_FAILURE);
    }

    _socket = std::make_unique<Socket>(Socket::Domain::INET, Socket::Type::DGRAM, 0);
    if (_socket->getDescriptor() < 0)
    {
        free(&ifr);
        if_freenameindex(nameIndex);
        std::cerr << "ERROR: can't create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (i = nameIndex; !(i->if_index == 0 && i->if_name == nullptr); i++)
    {
        strcpy(ifr.ifr_name, i->if_name);
        ioctl(_socket->getDescriptor(), SIOCGIFFLAGS, &ifr);
        std::cout << i->if_index << ": " << i->if_name << " " << ((ifr.ifr_ifru.ifru_flags |= IFF_UP) ? "UP" : "DOWN") << std::endl;
    }

    if_freenameindex(nameIndex);
    cleanup();
    exit(EXIT_SUCCESS);
}

void Manager::printHelpAndExit()
{
    std::cout << "Observer 0.0.1 - network packet analyzer" << "\n";
    std::cout << "Usage: observer [-h] [-l] [-d=\'device\'] [-p=\'protocol\'] [-f=\'filename\']" << "\n" << "\n";
    std::cout << "       -h    Print help and exit\n";
    std::cout << "       -l    Print all network interfaces in system and exit\n";
    std::cout << "       -d    Set device for analyzing\n";
    std::cout << "       -p    Set protocol for analyzing\n";
    std::cout << "       -f    Set output file\n";
    exit(EXIT_SUCCESS);
}

void Manager::openInterface()
{
    struct sockaddr_ll saddrll;
    memset(&saddrll, 0, sizeof(saddrll));
    unsigned int devIndex = 0;
    if (_device != "")
    {
        devIndex = getDeviceIndex(_device);
    }

    if (devIndex == 0)
    {
        // We have "any" device
        _socket = std::make_unique<Socket>(Socket::Domain::PACKET, Socket::Type::DGRAM, 0);
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create UDP socket");
        }
    }
    else
    {
        // We specified concrete device and now can open raw socket
        _socket = std::make_unique<Socket>(Socket::Domain::PACKET, Socket::Type::RAW, htons(_protocol));
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create RAW socket");
        }
    }

    // TODO: we need to bind socket to device which we want to observe
    saddrll.sll_family = AF_PACKET;
    saddrll.sll_protocol = htons(_protocol);
    saddrll.sll_ifindex = devIndex;
    
    if (bind(_socket->getDescriptor(), (const sockaddr*)&saddrll, sizeof(saddrll)) < 0)
    {
        if (errno == ENODEV)
        {
            throw Exception("ERROR: no such device");
        }
        else if (errno == ENETDOWN)
        {
            throw Exception("ERROR: network is down");
        }
        else 
        {
            throw Exception("ERROR: unknown error: " + std::to_string(errno));
        }
    }
}

int Manager::getProtocolByName(const std::string& name) const
{
    if (name == "IPv4")
    {
        return static_cast<int>(Protocols::IPv4);
    }
    else if (name == "IPv6")
    {
        return static_cast<int>(Protocols::IPv6);
    }
    else if (name == "ARP")
    {
        return static_cast<int>(Protocols::ARP);
    }
    else if (name == "ALL")
    {
        return static_cast<int>(Protocols::ALL);
    }
    return 0;
}

std::string Manager::getOption(char* option)
{
    return std::string(option);
}

unsigned int Manager::getDeviceIndex(const std::string& name) const
{
    return if_nametoindex(name.c_str());
}
