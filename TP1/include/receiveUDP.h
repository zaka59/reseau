#ifndef RECEIVEUDP_H
#define RECEIVEUDP_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 512
#define PORT     8080

int receiveUDP(int *sockfd, char *buffer,int port, struct sockaddr_in addr);

#endif
