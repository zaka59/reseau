#include "../include/sendUDP.h"


int sendUDP(const char* ip_address,const char* port, unsigned char*msg, int size_msg,int *sockfd_param){

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip_address);
    /* for(int i =0;i<size_msg;i++) */
    /*     printf("%c",msg[i]); */
    /*  */
    /* printf("\n"); */

    *sockfd_param = socket(PF_INET, SOCK_DGRAM, 0);
    if(*sockfd_param<0)
        return -1;

    int res = sendto(*sockfd_param,
                     msg,
                     size_msg,
                     0,
                     (struct sockaddr*) &addr,
                     sizeof(addr)
                    );

    if(res<0) return  1;
    return 0;

}


#ifndef DNS
/* int main(int argc, char ** argv){ */
/*     if(argc != 4){ */
/*         printf("usage : sendUDP <ip_address> <port> <msg>"); */
/*         return -1; */
/*     } */
/*     const char *ip_address = argv[1]; */
/*     const char *port = argv[2]; */
/*     const char *msg = argv[3]; */
/*  */
    /* int *sockfd;*/
/*     int res = sendUDP(ip_address,port, (unsigned char *) msg,strlen((const char*)msg),sockfd); */
/*     assert(res==0); */
/*     return 0; */
/*  */
/* } */
#endif
