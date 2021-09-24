#include "manager/manager.h"

Manager::~Manager()
{
}

void Manager::init(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "e:i:d:f:lh")) != -1)
    {
        switch (opt)
        {
        case 'l':
            listDevicesAndExit();
        case 'd':
            _device = getOption(optarg);
            break;
        case 'e':
            _eProtocol = getEthernetProtoByName(getOption(optarg));
            break;
        case 'i':
            _iProtocol = getInternetProtoByName(getOption(optarg));
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

    ssize_t bsize = 0;
    Buffer *b = new Buffer(65535);

    bsize = recvfrom(_socket->getDescriptor(), b->getBuffer(), b->getCapacity(), 0, nullptr, nullptr);
    if (bsize == -1)
    {
        throw Exception("ERROR: Failed to get packets");
    }
    _parser = std::make_unique<Parser>();
    _parser->parse(b);
    EthernetHeader ethdrp = _parser->getEthernetHeader();
    IPHeader iphdrp = _parser->getIPHeader();

    std::cout << ethdrp;
    std::cout << iphdrp;
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
        std::cerr << "ERROR: if_nameindex() return null pointer" << std::endl;
        exit(EXIT_FAILURE);
    }

    _socket = std::make_unique<Socket>(Socket::Domain::INET, Socket::Type::DGRAM, static_cast<int>(IProtocols::IP));
    if (_socket->getDescriptor() < 0)
    {
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
    std::cout << "Observer 0.0.1 - network packet analyzer"
              << "\n";
    std::cout << "Usage: observer [-h] [-l] [-d=\'device\'] [-e=\'ethernet protocol\'] [-i=\'internet protocol\'] [-f=\'filename\']"
              << "\n"
              << "\n";
    std::cout << "       -h    Print help and exit\n";
    std::cout << "       -l    Print all network interfaces in system and exit\n";
    std::cout << "       -d    Set device for analyzing\n";
    std::cout << "       -e    Set ethernet protocol for analyzing\n";
    std::cout << "       -i    Set internet protocol for analyzing\n";
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
        _socket = std::make_unique<Socket>(Socket::Domain::PACKET, Socket::Type::DGRAM, static_cast<int>(IProtocols::IP));
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create UDP socket");
        }
    }
    else
    {
        // We specified concrete device and now can open raw socket
        _socket = std::make_unique<Socket>(Socket::Domain::PACKET, Socket::Type::RAW, htons(_iProtocol));
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create RAW socket");
        }
    }

    // TODO: we need to bind socket to device which we want to observe
    saddrll.sll_family = AF_PACKET;
    saddrll.sll_protocol = htons(_eProtocol);
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

int Manager::getEthernetProtoByName(const std::string& name) const
{
    if (name == "IPv4")
    {
        return static_cast<int>(EProtocols::IPv4);
    }
    else if (name == "IPv6")
    {
        return static_cast<int>(EProtocols::IPv6);
    }
    else if (name == "ARP")
    {
        return static_cast<int>(EProtocols::ARP);
    }
    else if (name == "ALL")
    {
        return static_cast<int>(EProtocols::ALL);
    }
    else
    {
        return static_cast<int>(EProtocols::IPv4);
    }
}

int Manager::getInternetProtoByName(const std::string& name) const
{
    if (name == "IP")
    {
        return static_cast<int>(IProtocols::IP);
    }
    else if (name == "TCP")
    {
        return static_cast<int>(IProtocols::TCP);
    }
    else if (name == "UDP")
    {
        return static_cast<int>(IProtocols::UDP);
    }
    else
    {
        return static_cast<int>(IProtocols::IP);
    }
}

std::string Manager::getOption(char* option)
{
    return std::string(option);
}

unsigned int Manager::getDeviceIndex(const std::string& name) const
{
    return if_nametoindex(name.c_str());
}
