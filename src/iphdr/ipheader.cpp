#include "iphdr/ipheader.h"

IPHeader::IPHeader()
{
    _ip = new iphdr;
}

IPHeader::~IPHeader()
{
    delete _ip;
}

void IPHeader::setIhl(uint8_t ihl)
{
    _ip->ihl = ihl;
}

void IPHeader::setVersion(uint8_t version)
{
    _ip->version = version;
}

void IPHeader::setTos(uint8_t tos)
{
    _ip->tos = tos;
}

void IPHeader::setTtl(uint8_t ttl)
{
    _ip->ttl = ttl;
}

void IPHeader::setId(uint16_t id)
{
    _ip->id = id;
}

void IPHeader::setLen(uint16_t tot_len)
{
    _ip->tot_len = tot_len;
}

void IPHeader::setChecksum(uint16_t check)
{
    _ip->check = check;
}

void IPHeader::setProtocol(uint8_t protocol)
{
    _ip->protocol = protocol;
}

void IPHeader::setSource(uint32_t saddr)
{
    _ip->saddr = saddr;
}

void IPHeader::setDestination(uint32_t daddr)
{
    _ip->daddr = daddr;
}

uint8_t IPHeader::getIhl() const
{
    return _ip->ihl;
}

uint8_t IPHeader::getVersion() const
{
    return _ip->version;
}

uint8_t IPHeader::getTos() const
{
    return _ip->tos;
}

uint8_t IPHeader::getTtl() const
{
    return _ip->ttl;
}

uint16_t IPHeader::getId() const
{
    return _ip->id;
}

uint16_t IPHeader::getLen() const
{
    return _ip->tot_len;
}

uint8_t IPHeader::getProtocol() const
{
    return _ip->protocol;
}

uint32_t IPHeader::getSource() const
{
    return _ip->saddr;
}

uint32_t IPHeader::getDestination() const
{
    return _ip->daddr;
}
