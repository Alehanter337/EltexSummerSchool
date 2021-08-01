#include "headers.h"
#include <stdio.h>

int main()
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	int port = 7331;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd_socket == ERROR) 
    {
        handle_error("socket()");
	}
    else
    {
        printf("|CLIENT| - Socket created\n");
    }

	char msg_1[] = "👋\0";
	sendto(fd_socket, msg_1, sizeof(msg_1), 0,
		(struct sockaddr *)&server, sizeof(struct sockaddr_in));

	connect(fd_socket, (struct sockaddr *)&server,
		sizeof(struct sockaddr_in));
	
    char msg_2[] = "✌🏼\0";
	send(fd_socket, msg_2, sizeof(msg_2), 0);

	close(fd_socket);
	exit(EXIT_SUCCESS);
}
