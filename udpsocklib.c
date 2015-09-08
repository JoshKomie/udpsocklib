#include "udpsocklib.h"

int sendPacket(const char* ipAddress, const char* port, const char *data)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    
    if ((rv = getaddrinfo(ipAddress, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("udpsocklib: socket error");
            continue;
        }
        
        break;
    }
    
    if (p == NULL) {
        fprintf(stderr, "udpsocklib: failed to create socket\n");
        return 2;
    }
    
    if ((numbytes = sendto(sockfd, data, strlen(data), 0,
                           p->ai_addr, p->ai_addrlen)) == -1) {
        perror("udpsocklib: sendto");
        exit(1);
    }
    
    freeaddrinfo(servinfo);
    
    if (DEBUG_MODE)
        printf("udpsocklib: sent %d bytes to %s\n", numbytes, ipAddress);
    close(sockfd);
    return 0;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int listenForPacket(const char* port, char **packetData)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("udpsocklib: socket");
            continue;
        }
        
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("udpsocklib: bind");
            continue;
        }
        
        break;
    }
    
    if (p == NULL) {
        fprintf(stderr, "udpsocklib: failed to bind socket\n");
        return 2;
    }
    
    freeaddrinfo(servinfo);
    if (DEBUG_MODE)
        printf("udpsocklib: waiting to recvfrom...\n");
    
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                             (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    if (DEBUG_MODE)
    printf("udpsocklib: got packet from %s\n",
           inet_ntop(their_addr.ss_family,
                     get_in_addr((struct sockaddr *)&their_addr),
                     s, sizeof s));
    if (DEBUG_MODE)
        printf("udpsocklib: packet is %d bytes long\n", numbytes);
    
    buf[numbytes] = '\0';
    *packetData = strdup(buf);
   //*packetSize = numbytes;
    
        if (DEBUG_MODE)
    printf("udpsocklib: packet contains \"%s\"\n", buf);
    
    close(sockfd);
    
    return 0;

}

int listenForPacketAndSource(const char* port, char **packetData, char **senderAddress)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("udpsocklib: socket");
            continue;
        }
        
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("udpsocklib: bind");
            continue;
        }
        
        break;
    }
    
    if (p == NULL) {
        fprintf(stderr, "udpsocklib: failed to bind socket\n");
        return 2;
    }
    
    freeaddrinfo(servinfo);
    if (DEBUG_MODE)
        printf("udpsocklib: waiting to recvfrom...\n");
    
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                             (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    if (DEBUG_MODE)
    printf("udpsocklib: got packet from %s\n",
           inet_ntop(their_addr.ss_family,
                     get_in_addr((struct sockaddr *)&their_addr),
                     s, sizeof s));
					 
	*senderAddress = strdup(inet_ntop(their_addr.ss_family,
                     get_in_addr((struct sockaddr *)&their_addr),
                     s, sizeof s));
    if (DEBUG_MODE)
        printf("udpsocklib: packet is %d bytes long\n", numbytes);
    
    buf[numbytes] = '\0';
    *packetData = strdup(buf);
   //*packetSize = numbytes;
    
        if (DEBUG_MODE)
    printf("udpsocklib: packet contains \"%s\"\n", buf);
    
    close(sockfd);
    
    return 0;

}