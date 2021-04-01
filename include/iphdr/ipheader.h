#ifndef IP_HEADER_H
#define IP_HEADER_H

#include <netinet/ip.h>
#include <cstdint>

class IPHeader
{
public:
    IPHeader();
    ~IPHeader();

    void setIhl(uint8_t ihl);
    void setVersion(uint8_t version);
    void setTos(uint8_t tos);
    void setTtl(uint8_t ttl);
    void setId(uint16_t id);
    void setLen(uint16_t tot_len);
    void setChecksum(uint16_t check);
    void setProtocol(uint8_t protocol);
    void setSource(uint32_t saddr);
    void setDestination(uint32_t daddr);

    uint8_t getIhl() const;
    uint8_t getVersion() const;
    uint8_t getTos() const;
    uint8_t getTtl() const;
    uint16_t getId() const;
    uint16_t getLen() const;
    uint16_t getChecksum() const;
    uint8_t getProtocol() const;
    uint32_t getSource() const;
    uint32_t getDestination() const;

private:
    struct iphdr* _ip;
};

#endif // IP_HEADER_H