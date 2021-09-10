#include "parser/parser.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

Parser::Parser()
{
}

void Parser::parse(Buffer* buffer)
{
    struct sockaddr_in source_socket_address, dest_socket_address;
    ssize_t saddrLength;

    struct ethhdr* eth = reinterpret_cast<struct ethhdr*>(buffer->getBuffer());
    
    _ether.setDestinationAddress(eth->h_dest);
    _ether.setSourceAddress(eth->h_source);
    _ether.setType(eth->h_proto);

    struct iphdr* ip = reinterpret_cast<struct iphdr*>(buffer->getBuffer() + sizeof (struct ethhdr));

    memset(&source_socket_address, 0, sizeof(source_socket_address));
    source_socket_address.sin_addr.s_addr = ip->saddr;
    _iphdr.setSource(inet_ntoa(source_socket_address.sin_addr));

    memset(&dest_socket_address, 0, sizeof(dest_socket_address));
    dest_socket_address.sin_addr.s_addr = ip->daddr;
    _iphdr.setDestination(inet_ntoa(dest_socket_address.sin_addr));

    _iphdr.setVersion(ip->version);
    _iphdr.setIhl(ip->ihl);
    _iphdr.setLen(ntohs(ip->tot_len));
    _iphdr.setId(ntohs(ip->id));
    _iphdr.setTtl(ip->ttl);
    _iphdr.setProtocol(ip->protocol);
    _iphdr.setChecksum(ntohs(ip->check));
}

EthernetHeader& Parser::getEthernetHeader()
{
    return _ether;
}

IPHeader& Parser::getIPHeader()
{
    return _iphdr;
}
