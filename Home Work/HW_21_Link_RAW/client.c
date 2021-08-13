#include "headers.h"
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void send_packet(struct sockaddr_ll, int, 
                 unsigned char [MAC_LEN], 
                 unsigned char [MAC_LEN]);

unsigned short csum(unsigned short *,int);

int main(void)
{
    unsigned char mac_source[MAC_LEN] = {0xa0, 0x78, 0x17, 0x069 0x9d, 0x11};
    unsigned char mac_dest[MAC_LEN] = {0xb8, 0x27, 0xeb, 0x12, 0x46, 0xd5};

    struct sockaddr_ll server;
    server.sll_family = AF_PACKET;
    server.sll_ifindex = if_nametoindex(INTERFACE);
    
    server.sll_halen = MAC_LEN;
    memmove((void *)(server.sll_addr), (void *)mac_dest, MAC_LEN);

    int fd_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
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
        send_packet(server, fd_socket, mac_source, mac_dest);
    }

    close(fd_socket);
    exit(EXIT_SUCCESS);
}

void send_packet(struct sockaddr_ll server, 
                 int fd_socket,
                 unsigned char mac_source[MAC_LEN], 
                 unsigned char mac_dest[MAC_LEN])
{
    socklen_t sockaddr_len = sizeof(struct sockaddr_ll);

    printf("|CLIENT| - Enter message: ");

    char *message = calloc(PACKET_SIZE - sockaddr_len, sizeof(char));
    fgets(message, PACKET_SIZE - sockaddr_len, stdin);

    char *packet = calloc(PACKET_SIZE, sizeof(char));
    memmove(packet + 
            sizeof(struct ether_header) + 
            sizeof(struct iphdr) + 
            sizeof(struct udphdr),
            message, 
            strlen(message) - 1);
    
    struct ether_header *ether_header;
    ether_header = (struct ether_header *) packet;
    for(int i = 0; i < MAC_LEN; i++)
    {
        ether_header->ether_shost[i] = mac_source[i];
        ether_header->ether_dhost[i] = mac_dest[i];
    }
    ether_header->ether_type = htons(ETHERTYPE_IP);

    struct iphdr *ip_header;
    ip_header = (struct iphdr *) (packet + sizeof(struct ether_header));
    ip_header->ihl = 5;
    ip_header->version = 4;
    ip_header->tos = 0;
    ip_header->id = htonl(601);
    ip_header->frag_off = 0;
    ip_header->ttl = 255;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->saddr = inet_addr(CLIENT_IP);
    ip_header->daddr = inet_addr(SERVER_IP);
    ip_header->tot_len = htons(ip_header->ihl * 4 + 
                              sizeof(struct udphdr) +
                              strlen(message) - 1);
    ip_header->check = 0;
    ip_header->check = csum((unsigned short *) ip_header,
                           ip_header->ihl * 4);


    struct udphdr *udp_header;
    udp_header = (struct udphdr *)
                 (packet + sizeof(struct ether_header) + sizeof(struct iphdr));
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
        
        ether_header = (struct ether_header *) packet;
        unsigned short mac_flag = 1;
        for(int i = 0; i < MAC_LEN; i++)
        {
            if(ether_header->ether_dhost[i] != mac_source[i])
            {
                mac_flag = 0;
                break;
            }
        }

        if(mac_flag == 0)
        {
            continue;
        }

        ip_header = (struct iphdr *)
                    (packet + sizeof(struct ether_header));
        struct in_addr addr;
        addr.s_addr = ip_header->daddr;
        if (strcmp(CLIENT_IP, inet_ntoa(addr)) != 0)
        {
            continue;
        }
        
        udp_header = (struct udphdr *) (packet + sizeof(struct ether_header) 
                    + ip_header->ihl * 4);
        

        if (ntohs(udp_header->dest) != CLIENT_PORT)
        {
            continue;
        }
        else if (ntohs(udp_header->dest) == CLIENT_PORT)
        {
            printf("|CLIENT| - Received new packet from server\n");
            printf("|CLIENT| - MAC: ");
            for (int i = 0; i < MAC_LEN; i++)
            {
                printf("%02X ", (int) ether_header->ether_dhost[i]);
            }
            printf("\n");
            printf("|CLIENT| - IP: %s\n", inet_ntoa(addr));
            printf("|CLIENT| - PORT: %d\n", ntohs(udp_header->dest));
            printf("|CLIENT| - Received packet: %d size\n", ret);
            printf("|CLIENT| - Message: %s\n\n", 
                  (packet + sizeof(struct ether_header) + 
                   ip_header->ihl * 4 + sizeof(struct udphdr)));
            break;
        }
    }

    free(message);
    free(packet);
}

unsigned short csum(unsigned short *ptr,int nbytes)
{
	register long sum = 0;
	unsigned short oddbyte;
	register short answer;

	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;

	return(answer);
}
