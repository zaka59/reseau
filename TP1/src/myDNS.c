#include "../include/myDNS.h"

#include "../include/receiveUDP.h"
#include "../include/sendUDP.h"



// 12 octets d'entete : identifiant de requete/parametres [RFC1035, 4.1.1]
unsigned char default_header[QR_HEADER_LEN] = {
    0x08,  0xbb,  0x01,  0x00,
    0x00,  0x01,  0x00,  0x00,
    0x00,  0x00,  0x00,  0x00,
};

void fill_header(unsigned char* query){
    /* memcpy(default_header, query, QR_HEADER_LEN); */
    for (int i = 0; i < QR_HEADER_LEN; i++)
        query[i] = default_header[i];
}

void fill_additional(unsigned char* query, int length){
    query[length-1] = 0x01; // QCLASS : IN
    query[length-2] = 0x00; // QCLASS : IN
    query[length-3] = 0x01; // QTYPE : A
    query[length-4] = 0x00; // QTYPE : A
    query[length-5] = 0x00; // terminator
}


/*
 * www.google.fr -> [3,6,2]
 */
void size_subdomains(char const *hostname,int *size_subdomains){
    int i = 0;
    int sub_domain = 0;
    int len = strlen(hostname);
    int j = 0;
    while (i <len){
        if (hostname[i++] == '.'){
            size_subdomains[sub_domain]=j;
            sub_domain++;
            j=0;
        }
        else 
            j++;
    }
    if(hostname[--i]!='.')size_subdomains[sub_domain]=j; // last subdomain
}

//nb subdomains of a given domain
int nb_subdomains(const char* hostname,int size_hostname){
    int res = 0;
    int i;
    for(i=0;i<size_hostname; i++){
        if(hostname[i]=='.') res++;
    }
    if(hostname[size_hostname-1]=='.'){
        res--;
    }
    if(hostname[0]!='.'){
        res++;
    }
    return res;
}

void fill_qname(char const* hostname,int size_hostname, unsigned char* query){
    int size_sds[nb_subdomains(hostname,size_hostname)];
    size_subdomains(hostname,size_sds);
    int subdomain = 0;
    int i = QR_HEADER_LEN+1;
    query[QR_HEADER_LEN] = size_sds[0];
    int j = -1; 
    while((++j)<size_hostname){
        /* printf("%c - %d \n",hostname[j],size_sds[subdomain]); */
        if ('.' != hostname[j]) query[i++] = hostname[j];
        else query[i++] = size_sds[++subdomain] ;
    }
    query[i] = 0x00; // zero terminator
}


int lookup(unsigned char *query, int size_query, const char *ip_address){
    int *sockfd;
    int res = sendUDP(ip_address, DNS_PORT, query,size_query, sockfd);
    if(res==-1)
        printf("socket error\n"); //debug
    else if (res==1)
        printf("sendto error\n"); //debug

    assert(res==0);
    struct sockaddr_in addr;
    addr.sin_family      = AF_INET; /* IPv4 */
    addr.sin_port        = htons(53); /* numero de port dest */
    addr.sin_addr.s_addr = inet_addr(ip_address); /* @IPv4 dest */

    unsigned char buffer[BUFF_SIZE];
    int length = receiveUDP(sockfd, (char *) buffer, 53, addr);
    print_response(buffer, length, addr,size_query);
    return 0;
}



void print_response(unsigned char *buffer, int length, struct sockaddr_in addr, size_t size_query){

    char *ip= inet_ntoa(addr.sin_addr);
    printf("Server : %s\n", ip);
    printf("Address : %s#%d\n", ip,ntohs(addr.sin_port));
    printf("\nNon-authoritative answer:\n");
    int nb_answer = *(buffer + 7);
    int answer = 1;
    unsigned char *next_answer = buffer + size_query;
    while (answer <= nb_answer){
        while (*next_answer != 0xc0) next_answer++; //adresse indicator
        next_answer = print_infos_answer(next_answer, buffer);
        answer++;
    }

    printf("\nHexa answer:\n");
    print_hexa_values(buffer,length);
}


unsigned char* print_infos_answer(unsigned char *answer,unsigned char * buffer){
    static int nb_answer = 0;
    int type = ((int) answer[3]);
    int size_answer = 12 + answer[11]; // + data's length

    if(nb_answer>0){
        int i = 1;
        unsigned char *c = ((int) answer[1])+buffer ;
        while (*c) {
            if (*c > 0 && *c <= 9 && !i) printf(".");
            else printf("%c", *c);
            c++;
            i = 0;
        }
        printf("\n");
    }
    if(type==5){ // if canonical name
        int first = 1;
        unsigned char *c = ((int) answer[1])+buffer ;
        while (*c) {
            if (*c > 0 && *c <= 9 && !first) printf(".");
            else printf("%c", *c);
            c++;
            first = 0;
        }
        printf(" canonical name = " );
    }
    else if (type == 1){ // if adresse
        printf("Name: ");
        int first = 1;
        unsigned char *c = ((int) answer[1])+buffer ;
        while (*c) {
            if (*c > 0 && *c <= 9 && !first) printf(".");
            else printf("%c", *c);
            c++;
            first = 0;
        }
        printf("\n");
        printf("Address: ");

        for (size_t i = 0; i < 4; i++) {
            int n = (answer+12)[i];
            if (n < 0) n += 256;
            printf("%d", n);
            if (i != 3) printf(".");
        }
        printf("\n");
    }
    else{
        /* printf("WTF\n"); */
    }
    fflush(stdout);
    nb_answer++;

    return answer + size_answer; // next answer if there is one

}

void print_hexa_values(unsigned char * buffer, int length){

    for (int i = 0; i < length; i++) {
        printf("%.2X ", buffer[i] & 0xff);
        if (((i+1)%16 == 0) || (i+1 == length)) {
            for (int j = i+1 ; j < ((i+16) & ~15); j++)
                printf("   ");
            printf("\t");
            for (int j = i & ~15; j <= i; j++)
                printf("%c", buffer[j] > 31 && buffer[j] < 128 ? (char) buffer[j] : '.');
            printf("\n");
        }
    }
    fflush(stdout);

}

#define MAIN
int main(int argc, char ** argv){

    if(argc > 3 || argc < 2){
        printf("Usage : myDNS <SYMB_SERVER> <IPV4_SERVER> \n");
        printf("\t exemple : myDNS  www.google.com 8.8.4.4 \n");
        printf("Or : myDNS <SYMB_SERVER>\n# this option will use the default IPV4_SERVER : 8.8.8.8\n");
        printf("\t exemple : myDNS www.google.com\n");
        exit(EXIT_FAILURE);
    }

    char const *hostname = argv[1];
    char *ip_address = DEFAULT_SERVER;

    if(argc == 3)
        ip_address = argv[2];

    int size_hostname = strlen(hostname);
    int size_query= QR_ADDIT_LEN+
        QR_HEADER_LEN+
        size_hostname+1
        ;

    //TODO : malloc inecessaire, query[size_query] suffit
    unsigned char *query = malloc(sizeof(unsigned char)*size_query);
    fill_header(query);
    fill_qname(hostname,size_hostname,query);
    fill_additional(query,size_query);

    /* for(int i=0; i<size_query;i++){ */
    /*     printf("%d : %x - ",i,query[i] & 0xff); */
    /*     if(i%10==0) printf("\n"); */
    /*  */
    /* } */
    /* fflush(stdout); */

    lookup(query, size_query, ip_address);

    free(query);
    return 0; 
}
