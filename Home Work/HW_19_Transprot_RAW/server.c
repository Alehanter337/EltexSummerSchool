#include "headers.h"

int socket_init(int);

int main(void)
{
    struct sockaddr_in client;
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }
    
    if(bind(fd_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        handle_error("bind()");
    }

    //int fd_socket = socket_init(PORT);  
    socklen_t sockaddr_len = sizeof(struct sockaddr_in);
    while (1) 
    {
        printf("|SERVER| - Whaiting UDP packet from client...\n ");
        
        memset(&client, 0, sizeof(client));

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
}
/*
int socket_init(int port)
{
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fd_socket < 0)
    {
        handle_error("socket()");
    }
    
    if(bind(fd_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        handle_error("bind()");
    }

    return fd_socket;
}
*/
