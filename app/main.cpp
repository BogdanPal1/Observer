#include "socket/rawsocket.h"
#include "buffer/buffer.h"
#include "iphdr/ipheader.h"
#include <netinet/ip.h>
#include <netdb.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[])
{
    struct sockaddr_in source_socket_address, dest_socket_address;
    ssize_t saddrLength;

    // Creating raw socket
    RawSocket socket = RawSocket::getInstance();
    int desc = 0;
    desc = socket.getDescriptor();
    if (desc < 0)
    {
        std::cerr << "Can't create socket!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Socket created with descriptor: " << desc << std::endl;
    Buffer *b = new Buffer(65535);
    ssize_t bsize = 0;
    while (true)
    {
        bsize = recvfrom(desc, b->getBuffer(), b->getCapacity(), 0, nullptr, nullptr);
        if (bsize == -1)
        {
            printf("Failed to get packets\n");
            socket.closeSocket();
            return 1;
        }
        IPHeader* ip_hdr = (IPHeader*)b;
        //struct iphdr *ip_packet = (struct iphdr *)(b->getBuffer());

        memset(&source_socket_address, 0, sizeof(source_socket_address));
        source_socket_address.sin_addr.s_addr = ip_hdr->getSource();
        memset(&dest_socket_address, 0, sizeof(dest_socket_address));
        dest_socket_address.sin_addr.s_addr = ip_hdr->getDestination();

        printf("Incoming Packet: \n");
        printf("Packet Size (bytes): %d\n", ntohs(ip_hdr->getLen()));
        printf("Source Address: %s\n", (char *)inet_ntoa(source_socket_address.sin_addr));
        printf("Destination Address: %s\n", (char *)inet_ntoa(dest_socket_address.sin_addr));
        printf("Identification: %d\n\n", ntohs(ip_hdr->getId()));

        if(bsize > 4096) {
            socket.closeSocket();
            exit(EXIT_SUCCESS);
        }
    }
    socket.closeSocket();
    std::cout << bsize << std::endl;
    exit(EXIT_SUCCESS);
}
