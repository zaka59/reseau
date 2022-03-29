#ifndef SENDUDP_H
#define SENDUDP_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 512
#define PORT     8080

int sendUDP(const char* ip_address,const char* port, unsigned char*msg,int size_msg, int *sockfd_param);

#endif
