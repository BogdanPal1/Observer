#include "ethr/ethernetheader.h"
#include <iomanip>

const unsigned short EthernetHeader::MAC_LEN = 6;

EthernetHeader::EthernetHeader()
{
    _srcAddr.fill(0x0);
    _destAddr.fill(0x0);
    _protocolType = 0;
}
 
void EthernetHeader::setDestinationAddress(const unsigned char* destination)
{
    for (size_t i = 0; i < MAC_LEN; ++i)
        _destAddr[i] = destination[i];
}

void EthernetHeader::setSourceAddress(const unsigned char* source)
{
    for (size_t i = 0; i < MAC_LEN; ++i)
        _srcAddr[i] = source[i];
}

const std::array<unsigned char, 6>& EthernetHeader::getDestinationAddress() const
{
    return _destAddr;
}

const std::array<unsigned char, 6>& EthernetHeader::getSourceAddress() const
{
    return _srcAddr;
}

void EthernetHeader::setType(unsigned short protocol)
{
    _protocolType = protocol;
}

unsigned short EthernetHeader::getType() const
{
    return _protocolType;
}

std::ostream& operator<<(std::ostream& os, const EthernetHeader& header)
{
    os << "Source mac: "; 
    for (auto i : header._srcAddr)
        os << std::setw(2) << std::setfill('0') <<  std::hex << static_cast<unsigned int>(i) << " ";
    os << std::endl;

    os << "Destination mac: ";
    for (auto i : header._destAddr)
        os << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned int>(i) << " ";
    os << std::endl;

    os << "Protocol: " << std::dec << header._protocolType << "\n";
    return os;
}
