#include "headers.h"

void *threads_func(void *args);

int main(void)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    int port = 7331;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    int val = 0;
    
    int fd_socket = socket(AF_INET, SOCK_STREAM, val);
    if(fd_socket == ERROR)
    {
        handle_error("socket()");
    }
    else
    {
        printf("|SERVER| - Socket created\n");
    }
   
    int req = bind(fd_socket, (const struct sockaddr *) &server, 
                  sizeof(struct sockaddr_in)); 
    
    if(req == ERROR)
    {
        handle_error("bind()");
    }
    else
    {
        printf("|SERVER| - Bind complete\n");
    }

    if(listen(fd_socket, 1) == ERROR)
    {
        handle_error("listen()");
    }
    else
    {
        printf("|SERVER| - Listen done\n");
    }
    
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);

    pthread_t threads[MAX_SOCKET_VALUE];
    int fd_data[MAX_SOCKET_VALUE];
    
    for (int i = 0; i < MAX_SOCKET_VALUE; i++)
    {
        fd_data[i] = IS_EMPTY; 
    }
    
    for (int i = 0; i < MAX_SOCKET_VALUE; i++) 
    {
		if (i == MAX_SOCKET_VALUE)
        {
            i = 0;
        }

		if (fd_data[i] != IS_EMPTY)
        {
			continue;
        }
		
        printf("|SERVER| - Accept...\n");
		fd_data[i] = accept(fd_socket, NULL, NULL);
		if (fd_data[i] == ERROR) 
        {
		    handle_error("accept()");
        }
        else
        {
            printf("|SERVER| - accept");
        }

		void *param = (void *)&fd_data[i];
		if (pthread_create(&threads[i], &thread_attr, threads_func, param)) 
        {
		    handle_error("create()");
        }
        else {
            printf("|SERVER| - Thread created\n");
        }
	}
    
    close(fd_socket);
    exit(EXIT_SUCCESS);
}

void *threads_func(void *args)
{
    int *fd_data = (int*)args;

	while(1) 
    {
    	char buffer[BUFFER_SIZE] = {0};
		int ret = recv(*fd_data, buffer, BUFFER_SIZE, 0);
		if (ret == ERROR) 
        {
		    handle_error("recv()");
		}
        else
        {
            printf("|THREAD| - Recv done\n");
        }

		printf("|THREAD| - Msg received: %s\n", buffer);

		if (strncmp(buffer, "/exit", BUFFER_SIZE) == 0) 
        {
			printf("|THREAD| - fd_data close %d\n", *fd_data);
			close(*fd_data);
			*fd_data= IS_EMPTY;
			pthread_exit(0);
		}

		strcat(buffer, " Echo from SERVER");
		ret = send(*fd_data, buffer, BUFFER_SIZE, 0);
		if (ret == ERROR) 
        {
		    handle_error("send()");
        }
        else 
        {
            printf("|THREAD| - send done");
        }
		printf("MSG send: %s\n", buffer);
	}
}
