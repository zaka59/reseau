#ifndef MYDNS_H

#define MYDNS_H

#include <stddef.h>
#include <errno.h> 
#include <netdb.h> 
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 512
#define QR_HEADER_LEN  12 // 12 octets d'entete
#define QR_ADDIT_LEN 5
#define DEFAULT_SERVER "8.8.8.8"

#define DNS_PORT "53"




void fill_header(unsigned char* query);
    

void fill_additional(unsigned char* query, int length);


/*
 * www.google.fr -> [3,6,2]
 */
void size_subdomains(char const *hostname, int *size_subdomains);


void fill_qname(char const* hostname,int size_hostname, unsigned char* query);
 

int lookup(unsigned char *query,int size_query, const char *ip_address);

int nb_subdomains(const char* hostname, int size_hostname);

void print_response(unsigned char *buffer, int length, struct sockaddr_in addr, size_t size_query);

// it also returns the next answer
unsigned char* print_infos_answer(unsigned char *answer,unsigned char * buffer);

void print_hexa_values(unsigned char * buffer, int length);
#endif
