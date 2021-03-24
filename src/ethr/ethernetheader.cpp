#include "../../include/ethr/ethernetheader.h"

EthernetHeader::EthernetHeader()
{
    _destAddr.reserve(ETH_ALEN);
    _srcAddr.reserve(ETH_ALEN);
}

EthernetHeader::~EthernetHeader()
{

}

void EthernetHeader::setDestinationAddress()
{
    for (int i = 0; i < ETH_ALEN; ++i)
        _destAddr.push_back(_header.h_dest[i]);
}

const std::vector<unsigned char>& EthernetHeader::getDestinationAddress() const
{
    return _destAddr;
}
