#ifndef OBSERVER_PARSER_H
#define OBSERVER_PARSER_H

#include "ethr/ethernetheader.h"
#include "iphdr/ipheader.h"
#include "buffer/buffer.h"
#include <memory>

class Parser
{
public:
    Parser();
    void parse(Buffer* buffer);
    EthernetHeader& getEthernetHeader();
    IPHeader& getIPHeader();
private:
    EthernetHeader _ether;
    IPHeader _iphdr;
};

#endif // OBSERVER_PARSER_H
