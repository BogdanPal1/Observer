#include "iphdr/ipheader.h"

IPHeader::IPHeader()
{
}

void IPHeader::setIhl(uint8_t ihl)
{
    _ihl = ihl;
}

void IPHeader::setVersion(uint8_t version)
{
    _version = version;
}

void IPHeader::setTos(uint8_t tos)
{
    _tos = tos;
}

void IPHeader::setTtl(uint8_t ttl)
{
    _ttl = ttl;
}

void IPHeader::setId(uint16_t id)
{
    _id = id;
}

void IPHeader::setLen(uint16_t tot_len)
{
    _tot_len = tot_len;
}

void IPHeader::setChecksum(uint16_t check)
{
    _checksum = check;
}

void IPHeader::setProtocol(uint8_t protocol)
{
    _protocol = protocol;
}

void IPHeader::setSource(const char* source)
{
    _source.assign(source);
}

void IPHeader::setDestination(const char* destination)
{
    _destination.assign(destination);
}

uint8_t IPHeader::getIhl() const
{
    return _ihl;
}

uint8_t IPHeader::getVersion() const
{
    return _version;
}

uint8_t IPHeader::getTos() const
{
    return _tos;
}

uint8_t IPHeader::getTtl() const
{
    return _ttl;
}

uint16_t IPHeader::getId() const
{
    return _id;
}

uint16_t IPHeader::getLen() const
{
    return _tot_len;
}

uint8_t IPHeader::getProtocol() const
{
    return _protocol;
}

const std::string& IPHeader::getSource() const
{
    return _source;
}

const std::string& IPHeader::getDestination() const
{
    return _destination;
}
