#ifndef OBSERVER_ETHERNET_HEADER_H
#define OBSERVER_ETHERNET_HEADER_H

#include <ostream>
#include <array>

/**
 * @brief The Ethernet Protocols enumeration
 * 
 */
enum class EProtocols
{
    IPv4 = 0x0800,
    IPv6 = 0x86DD,
    ARP  = 0x0806,
    ALL  = 0x0003,
};

class EthernetHeader
{
public:
    void setDestinationAddress(const unsigned char* destination);
    void setSourceAddress(const unsigned char* source);
    void setType(unsigned short protocol);

    const std::array<unsigned char, 6>& getDestinationAddress() const;
    const std::array<unsigned char, 6>& getSourceAddress() const;
    unsigned short getType() const;

    friend std::ostream& operator<<(std::ostream& os, const EthernetHeader& header);

public:
    static const unsigned short MAC_LEN = 6;

private:
    std::array<unsigned char, 6> _destAddr{0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    std::array<unsigned char, 6> _srcAddr{0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    unsigned short _protocolType = 0;
};

#endif // OBSERVER_ETHERNET_HEADER_H
