#include "observer/observer.h"

Observer::Observer()
{
}

Observer::~Observer()
{
}

void Observer::init(int argc, char *argv[])
{
    struct sockaddr_ll saddrll = {0};
    int opt;

    while ((opt = getopt(argc, argv, "d:l")) != -1)
    {
        switch (opt)
        {
        case 'l':
            listDevicesAndExit();
            break;

        case 'd':
            _device = optarg;
            break;

        case '?':
            std::cout << "Unknown option: " << optopt << std::endl;
            break;
        }
    }

    saddrll.sll_family = AF_PACKET;
    saddrll.sll_ifindex = getDeviceIndex(_device);
    saddrll.sll_protocol = 0;
}

void Observer::listDevicesAndExit()
{
    struct if_nameindex *nameIndex, *i;
    struct ifreq iReq;
    int dUDP;

    nameIndex = if_nameindex();
    if (nameIndex == nullptr)
    {
        std::cerr << "if_nameindex() return null pointer" << std::endl;
        exit(EXIT_FAILURE);
    }

    dUDP = socket(AF_INET, SOCK_DGRAM, 0);
    if (dUDP < 0)
    {
        std::cerr << "Can't create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (i = nameIndex; !(i->if_index == 0 && i->if_name == nullptr); i++)
    {
        strcpy(iReq.ifr_name, i->if_name);
        int m = ioctl(dUDP, SIOCGIFFLAGS, &iReq);
        std::cout << i->if_index << ": " << i->if_name << " " << ((iReq.ifr_ifru.ifru_flags |= IFF_UP) ? "UP" : "DOWN") << std::endl;
    }

    if_freenameindex(nameIndex);
    close(dUDP);
    exit(EXIT_SUCCESS);
}

int Observer::getDeviceIndex(char *name) const
{
    struct ifreq iReq = {0};

    int sockd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockd < 0)
    {
        std::cerr << "Can't create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    int ioctlResult = ioctl(sockd, SIOCGIFINDEX, name, &iReq);
    close(sockd);

    return iReq.ifr_ifru.ifru_ivalue;
}