#include "observer/observer.h"

Observer::Observer() : _device(nullptr), _protocol(0), _sockd(-1)
{

}

Observer::~Observer()
{
}

void Observer::init(int argc, char *argv[])
{
    struct sockaddr_ll saddrll = {0};
    int opt;

    while ((opt = getopt(argc, argv, "i:d:l")) != -1)
    {
        switch (opt)
        {
        case 'l':
            listDevicesAndExit();
            break;

        case 'd':
            _device = getOption(optarg);
            break;

        case 'i':
            _protocol = getProtocolByName(getOption(optarg));
            break;

        case '?':
            std::cout << "Unknown option: " << optopt << std::endl;
            break;
        }
    }

    openInterface();
}

void Observer::cleanup()
{
    if (_sockd >= 0)
    {
        close(_sockd);
        std::cout << "Socket closed" << std::endl;
    }

    delete [] _buffer;
}

void Observer::listDevicesAndExit()
{
    struct if_nameindex *nameIndex, *i;
    struct ifreq ifr = {0};
    int sockd;

    nameIndex = if_nameindex();
    if (nameIndex == nullptr)
    {
        std::cerr << "if_nameindex() return null pointer" << std::endl;
        exit(EXIT_FAILURE);
    }

    sockd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockd < 0)
    {
        std::cerr << "Can't create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (i = nameIndex; !(i->if_index == 0 && i->if_name == nullptr); i++)
    {
        strcpy(ifr.ifr_name, i->if_name);
        int m = ioctl(sockd, SIOCGIFFLAGS, &ifr);
        std::cout << i->if_index << ": " << i->if_name << " " << ((ifr.ifr_ifru.ifru_flags |= IFF_UP) ? "UP" : "DOWN") << std::endl;
    }

    if_freenameindex(nameIndex);
    close(sockd);
    exit(EXIT_SUCCESS);
}

void Observer::openInterface()
{
    unsigned int devIndex = 0;
    if (_device != nullptr)
    {
        devIndex = getDeviceIndex(_device);
    }

    if (devIndex == 0)
    {
        // We have "any" device
        _sockd = socket(AF_PACKET, SOCK_DGRAM, 0);
        if (_sockd < 0)
        {
            std::cerr << "Can't open UDP socket. " << errno << std::endl;
            //exit(EXIT_FAILURE);
        }
    }
    else
    {
        // We specified concrete device and now can open raw socket
        _sockd = socket(AF_PACKET, SOCK_RAW, htons(_protocol));
        if (_sockd < 0)
        {
            std::cerr << "Can't open RAW socket" << std::endl;
            //exit(EXIT_FAILURE);
        }
    }

    // TODO: we need to bind socket to device which we want to observe
}

int Observer::getProtocolByName(char *name) const
{
    if (strcmp(name, "IPv4") == 0)
    {
        return static_cast<int>(Protocols::IPv4);
    }
    else if (strcmp(name, "IPv6") == 0)
    {
        return static_cast<int>(Protocols::IPv6);
    }
    else if (strcmp(name, "ARP") == 0)
    {
        return static_cast<int>(Protocols::ARP);
    }
    return 0;
}

char* Observer::getOption(char* option)
{
    size_t size = 16;
    _buffer = new char[size + 1];

    snprintf(_buffer, size, "%s", option);
    return _buffer;
}

unsigned int Observer::getDeviceIndex(char *name) const
{
    return if_nametoindex(name);
}
