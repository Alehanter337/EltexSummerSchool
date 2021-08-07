#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int socket_init(struct sockaddr_in, int);
void send_packet(struct sockaddr_in, int);

int main(void)
{
    struct sockaddr_in server;
    //int fd_socket = socket_init(server, PORT); 
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }
 
    while(1)
    {   
        send_packet(server, fd_socket);
    }

    close(fd_socket); 
    exit(EXIT_SUCCESS);
}
/*
int socket_init(struct sockaddr_in server, int port)
{
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    int fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }
    
    return fd_socket;
}
*/
void send_packet(struct sockaddr_in server, int fd_socket)
{
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    
    printf("|CLIENT| - Enter message: ");

    char *message = calloc(PACKET_SIZE - sockaddr_len, sizeof(char));
    fgets(message, PACKET_SIZE - sockaddr_len, stdin);
    
    char *packet = calloc(PACKET_SIZE, sizeof(char));
    memmove(packet + 8, message, strlen(message) - 1);
    
    int client_port = 7788;
    struct udphdr *udp_header;
    udp_header = (struct udphdr *)packet;
    udp_header->source = htonl(client_port);
    udp_header->dest = htonl(PORT);
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
        
        if (ntohs(udp_header->dest) == client_port) 
        {
            struct in_addr server_addr;
            server_addr.s_addr = ip_header->saddr;
            
            printf("|CLIENT| - Server IP: %s, Source PORT: %d, Destination PORT: %d\n",
                    inet_ntoa(server_addr), 
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
