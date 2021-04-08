#include "observer/observer.h"

Observer::Observer() : _device(""), _protocol(0), _sockd(-1)
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
        throw Exception("ERROR: can't create socket");
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
    if (_device != "")
    {
        devIndex = getDeviceIndex(_device);
    }

    if (devIndex == 0)
    {
        // We have "any" device
        _socket = std::unique_ptr<Socket>(new Socket(Socket::Type::DGRAM, 0));
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create UDP socket");
        }
    }
    else
    {
        // We specified concrete device and now can open raw socket
        _socket = std::unique_ptr<Socket>(new Socket(Socket::Type::RAW, htons(_protocol)));
        if (_socket->getDescriptor() < 0)
        {
            throw Exception("ERROR: can't create RAW socket");
        }
    }

    // TODO: we need to bind socket to device which we want to observe
}

int Observer::getProtocolByName(const std::string& name) const
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
    return 0;
}

std::string Observer::getOption(char* option)
{
    size_t size = 16;
    _buffer = std::unique_ptr<char[]>(new char[size + 1]);

    snprintf(_buffer.get(), size, "%s", option);
    return std::string(_buffer.get());
}

unsigned int Observer::getDeviceIndex(const std::string& name) const
{
    return if_nametoindex(name.c_str());
}
