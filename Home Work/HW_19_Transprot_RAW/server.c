#include "headers.h"
#include <stdlib.h>
int main(void)
{
    struct sockaddr_in client;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = INADDR_ANY;
        
    int fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }
    
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    
    int ret = bind(fd_socket, (struct sockaddr *)&server, sockaddr_len);
    if(ret < 0)
    {
        handle_error("bind()");
    }

    while (1) 
    {
        printf("|SERVER| - Whaiting UDP packet from client...\n ");
        
        memset(&client, 0, sizeof(struct sockaddr_in));

        sockaddr_len = sizeof(struct sockaddr_in);

        char packet[PACKET_SIZE] = {0};
         
        int ret = recvfrom(fd_socket, packet, PACKET_SIZE, 0, 
                          (struct sockaddr *)&client, &sockaddr_len);
        if(ret < 0)
        {
            handle_error("recvfrom()");
        }

        printf("|SERVER| - Client IP: %s, Client PORT: %d\n", 
                inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        printf("|SERVER| - Message: %d, Bytes: %s\n", ret, packet);
    
        strcat(packet, " from server");
        
        ret = sendto(fd_socket, packet, strlen(packet) * sizeof(char), 0,
                    (struct sockaddr*)&client, sockaddr_len);

        if(ret < 0)
        {
            handle_error("sendto()");
        }

        printf("|SERVER| - Echo-reply, size: %d\n", ret);
    }

    exit(EXIT_SUCCESS);
}
