#include "ethr/ethernetheader.h"

EthernetHeader::EthernetHeader()
{
    _eth = new ethhdr;
}

EthernetHeader::~EthernetHeader()
{
    delete _eth;
}

void EthernetHeader::setDestinationAddress(unsigned char* destination)
{
    for (int i = 0; i < ETH_ALEN; ++i)
        _eth->h_dest[i] = destination[i];
}

void EthernetHeader::setSourceAddress(unsigned char* source)
{
    for (int i = 0; i < ETH_ALEN; ++i)
        _eth->h_source[i] = source[i];
}

unsigned char* EthernetHeader::getDestinationAddress() const
{
    return _eth->h_dest;
}

unsigned char* EthernetHeader::getSourceAddress() const
{
    return _eth->h_source;
}

void EthernetHeader::setType(unsigned short protocolType)
{
    _eth->h_proto = protocolType;
}

unsigned short EthernetHeader::getType() const
{
    return _eth->h_proto;
}
