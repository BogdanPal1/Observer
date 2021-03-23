#ifndef ETHERNET_HEADER_H
#define ETHERNET_HEADER_H

#include <netinet/if_ether.h>
#include <ctype.h>

#include <vector>

class EthernetHeader
{
public:
    EthernetHeader();
    ~EthernetHeader();

    void setDestinationAddress();
    void setSourceAddress();

    const std::vector<unsigned char>& getDestinationAddress() const;
    std::vector<unsigned char>& getSourceAddress() const;
    unsigned short getType() const;

private:
    struct ethhdr _header;
    std::vector<unsigned char> _destAddr;
    std::vector<unsigned char> _srcAddr;
};

#endif // ETHERNET_HEADER_H