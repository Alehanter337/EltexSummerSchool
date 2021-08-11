#include "headers.h"
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>

void send_packet(struct sockaddr_in, int);

int main(void)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }

    int flag = 1;
    const int *flag_ptr = &flag;
    int ret = setsockopt(fd_socket, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag));
    if(ret < 0)
    {
        handle_error("setsocopt()");
    }
    
    while(1)
    {
        send_packet(server, fd_socket);
    }

    close(fd_socket);
    exit(EXIT_SUCCESS);
}

void send_packet(struct sockaddr_in server, int fd_socket)
{
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);

    printf("|CLIENT| - Enter message: ");

    char *message = calloc(PACKET_SIZE - sockaddr_len, sizeof(char));
    fgets(message, PACKET_SIZE - sockaddr_len, stdin);

    char *packet = calloc(PACKET_SIZE, sizeof(char));
    memmove(packet + sizeof(struct iphdr) + sizeof(struct udphdr),
            message, strlen(message) - 1);

    struct iphdr *ip_header;
    ip_header = (struct iphdr *)packet;
    ip_header->ihl = 5;
    ip_header->version = 4;
    ip_header->tos = 0;
    ip_header->id = htonl(601);
    ip_header->frag_off = 0;
    ip_header->ttl = 255;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->saddr = INADDR_ANY;
    ip_header->daddr = server.sin_addr.s_addr;

    struct udphdr *udp_header;
    udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));
    udp_header->source = htons(CLIENT_PORT);
    udp_header->dest = htons(SERVER_PORT);
    udp_header->check = 0;
    udp_header->len = htons(strlen(message) - 1 + sizeof(struct udphdr));

    int ret = sendto(fd_socket, packet, PACKET_SIZE, 0,
                     (struct sockaddr *)&server, sockaddr_len);
    if(ret < 0)
    {
        handle_error("sendto()");
    }

    printf("|CLIENT| - Sended to server %d \n", ret);

    while(1)
    {
        ret = recvfrom(fd_socket, packet, PACKET_SIZE, 0,
                       (struct sockaddr*)&server, &sockaddr_len);
        if(ret < 0)
        {
            handle_error("recvfrom()");
        }

        struct iphdr *ip_header = (struct iphdr *)packet;
        udp_header = (struct udphdr *) (packet + sizeof(struct iphdr));

        if (ntohs(udp_header->dest) == CLIENT_PORT)
        {
            struct in_addr saddr;
            saddr.s_addr = ip_header->saddr;

            printf("|CLIENT| - Server IP: %s, Source PORT: %d, Destination PORT: %d\n",
                    inet_ntoa(saddr),
                    ntohs(udp_header->source),
                    ntohs(udp_header->dest));

            printf("|CLIENT| - Received packet: %d\n", ret);

            printf("|CLIENT| - Message: %s\n\n",
                    packet + sizeof(struct iphdr) + sizeof(struct udphdr));

            break;
        }
    }

    free(message);
    free(packet);
}
