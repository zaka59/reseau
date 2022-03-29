#include "../include/receiveUDP.h"


int receiveUDP(int *sockfd, char *buffer,int port, struct sockaddr_in addr){
    int res;    
 socklen_t len = sizeof(struct sockaddr_in);
    res = recvfrom(*sockfd, buffer, BUFF_SIZE, 0,(struct sockaddr *) &addr, &len);
    assert(res!=-1);
    return res; 
}



#ifndef DNS
/* int main(int argc, char ** argv){ */
/*  */
/*     if(argc != 2){ */
/*         printf("usage : receiveUDP <port> "); */
/*         return -1; */
/*     } */
/*  */
/*     char buffer[BUFF_SIZE]; */
/*     struct sockaddr_in addr; */
/*     char *port = argv[1]; */
/*  */
/*     addr.sin_family = AF_INET; */
/*     addr.sin_port = htons(atoi(port)); */
/*     addr.sin_addr.s_addr = INADDR_ANY; */
/*  */
/*     int sockfd = socket(AF_INET, SOCK_DGRAM, 0); */
/*  */
/*     assert(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) != -1); */
/*     while(1){ */
/*         receiveUDP(sockfd, buffer, atoi(port), addr); */
/*         printf("%s\n", buffer); */
/*         memset(buffer, 0, BUFF_SIZE); */
/*     } */
/*     return 0; */
/*  */
/* } */
#endif
