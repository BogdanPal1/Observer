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

    void setDestinationAddress(unsigned char* destination);
    void setSourceAddress(unsigned char* source);
    void setType(unsigned short protocolType);

    unsigned char* getDestinationAddress() const;
    unsigned char* getSourceAddress() const;
    unsigned short getType() const;

private:
    struct ethhdr* _header;
    std::vector<unsigned char> _destAddr;
    std::vector<unsigned char> _srcAddr;
};

#endif // ETHERNET_HEADER_H