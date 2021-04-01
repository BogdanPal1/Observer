#include "ethr/ethernetheader.h"

EthernetHeader::EthernetHeader()
{
    _header = new ethhdr;
}

EthernetHeader::~EthernetHeader()
{
    delete _header;
}

void EthernetHeader::setDestinationAddress(unsigned char* destination)
{
    for (int i = 0; i < ETH_ALEN; ++i)
        _header->h_dest[i] = destination[i];
}

void EthernetHeader::setSourceAddress(unsigned char* source)
{
    for (int i = 0; i < ETH_ALEN; ++i)
        _header->h_source[i] = source[i];
}

unsigned char* EthernetHeader::getDestinationAddress() const
{
    return _header->h_dest;
}

unsigned char* EthernetHeader::getSourceAddress() const
{
    return _header->h_source;
}

void EthernetHeader::setType(unsigned short protocolType)
{
    _header->h_proto = protocolType;
}

unsigned short EthernetHeader::getType() const
{
    return _header->h_proto;
}
