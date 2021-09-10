#ifndef ETHERNET_HEADER_H
#define ETHERNET_HEADER_H

#include <ostream>
#include <array>

class EthernetHeader
{
public:
    EthernetHeader();
    void setDestinationAddress(const unsigned char* destination);
    void setSourceAddress(const unsigned char* source);
    void setType(unsigned short protocol);

    const std::array<unsigned char, 6>& getDestinationAddress() const;
    const std::array<unsigned char, 6>& getSourceAddress() const;
    unsigned short getType() const;

    friend std::ostream& operator<<(std::ostream& os, const EthernetHeader& header);

public:
    static const unsigned short MAC_LEN;

private:
    std::array<unsigned char, 6> _destAddr;
    std::array<unsigned char, 6> _srcAddr;
    unsigned short _protocolType;
};

#endif // ETHERNET_HEADER_H
