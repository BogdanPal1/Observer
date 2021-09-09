#ifndef ETHERNET_HEADER_H
#define ETHERNET_HEADER_H

#include <netinet/if_ether.h>
#include <ctype.h>

#include <array>
#include <vector>

class EthernetHeader
{
public:
    EthernetHeader();
    EthernetHeader(unsigned char* source, unsigned char* destination, unsigned short protocol);
    EthernetHeader(const EthernetHeader& other) = default;
    EthernetHeader& operator=(const EthernetHeader& other) = default;
    void setDestinationAddress(const unsigned char* destination);
    void setSourceAddress(const unsigned char* source);
    void setType(unsigned short protocol);

    // const std::array<unsigned char, 6>& getDestinationAddress() const;
    // const std::array<unsigned char, 6>& getSourceAddress() const;
    const std::vector<unsigned char>& getDestinationAddress() const;
    const std::vector<unsigned char>& getSourceAddress() const;
    unsigned short getType() const;

private:
    // std::array<unsigned char, 6> _destAddr{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
    // std::array<unsigned char, 6> _srcAddr{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}};
    std::vector<unsigned char> _destAddr;
    std::vector<unsigned char> _srcAddr;
    unsigned short _protocolType;
};

#endif // ETHERNET_HEADER_H
