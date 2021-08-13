#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <net/if.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define ERROR -1

#define SERVER_PORT 7331

#define CLIENT_PORT 7441

#define PACKET_SIZE 256

#define SERVER_IP "192.168.0.2"

#define CLIENT_IP "192.168.0.3"

#endif
