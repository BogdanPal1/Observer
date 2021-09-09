#include "ethr/ethernetheader.h"

EthernetHeader::EthernetHeader()
{
    _protocolType = 0;
}

EthernetHeader::EthernetHeader(unsigned char* source, unsigned char* destination, unsigned short protocol)
{
    for (size_t i = 0; i < ETH_ALEN; ++i)
    {
        _srcAddr.push_back(source[i]);
        _destAddr.push_back(destination[i]);
    }

    _protocolType = protocol;
}
 
void EthernetHeader::setDestinationAddress(const unsigned char* destination)
{
    for (size_t i = 0; i < ETH_ALEN; ++i)
        _destAddr.push_back(destination[i]);
}

void EthernetHeader::setSourceAddress(const unsigned char* source)
{
    for (size_t i = 0; i < ETH_ALEN; ++i)
        _srcAddr.push_back(source[i]);
}

const std::vector<unsigned char>& EthernetHeader::getDestinationAddress() const
{
    return _destAddr;
}

const std::vector<unsigned char>& EthernetHeader::getSourceAddress() const
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
