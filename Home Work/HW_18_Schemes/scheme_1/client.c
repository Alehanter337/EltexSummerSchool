#include "headers.h"
#include <stdio.h>

int main()
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	int port = 7331;
    server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int fd_data = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_data == ERROR) 
    {
	    handle_error("socket()");
    }
    else
    {
        printf("|CLIENT| - Socket created\n");
    }

	int req = connect(fd_data, (const struct sockaddr *) &server,
	                  sizeof(struct sockaddr_in));
	if (req == ERROR) 
    {
	    handle_error("connect()");
    }
    else
    {
        printf("|CLIENT| - Connect done\n");
    }

	while (1) 
    {
    	char buffer[BUFFER_SIZE] = {0};
		printf("MSG (/exit):\n");
		fgets(buffer, BUFFER_SIZE, stdin);

		req = send(fd_data, buffer, strlen(buffer) - 1, 0);
		if (req == ERROR) 
        {
		    handle_error("send()");
        }
        else
        {
            printf("|CLIENT| - Send complete\n");
        }
		printf("|CLIENT| - Send msg: %s", buffer);

		if (strncmp(buffer, "/exit", 3) == 0)
        {
			break;
        }

		req = recv(fd_data, buffer, BUFFER_SIZE, 0);
		if (req == ERROR) 
        {
		    handle_error("recv()");
        }
        else
        {
            printf("|CLIENT| - recv complete\n");
        }
		printf("|CLIENT| - Msg received: %s\n\n", buffer);
	}

	close(fd_data);
	exit(EXIT_SUCCESS);
}
