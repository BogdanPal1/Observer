#ifndef OBSERVER_IP_HEADER_H
#define OBSERVER_IP_HEADER_H

#include <string>
#include <cstdint>
#include <ostream>

class IPHeader
{
public:
    IPHeader();

    void setIhl(uint8_t ihl);
    void setVersion(uint32_t version);
    void setTos(uint8_t tos);
    void setTtl(uint8_t ttl);
    void setId(uint16_t id);
    void setLen(uint16_t tot_len);
    void setChecksum(uint16_t check);
    void setProtocol(uint8_t protocol);
    void setSource(const char* source);
    void setDestination(const char* destination);

    uint8_t getIhl() const;
    uint32_t getVersion() const;
    uint8_t getTos() const;
    uint8_t getTtl() const;
    uint16_t getId() const;
    uint16_t getLen() const;
    uint16_t getChecksum() const;
    uint8_t getProtocol() const;
    const std::string& getSource() const;
    const std::string& getDestination() const;

    friend std::ostream& operator<<(std::ostream& os, const IPHeader& header);

private:
    uint8_t _ihl;
    uint32_t _version;
    uint8_t _tos;
    uint16_t _id;
    uint8_t _ttl;
    uint16_t _tot_len;
    uint16_t _checksum;
    uint8_t _protocol;
    std::string _source;
    std::string _destination;
};

#endif // OBSERVER_IP_HEADER_H
