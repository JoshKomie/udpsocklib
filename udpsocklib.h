/* udpsocklib - easily send and recieve udp packets
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXBUFLEN 100
#define DEBUG_MODE 1
/*
 *
 */
int sendPacket(char* ipAddress, char* port, char* data);

int listenForPacket(char* port, char*packetData, int *packetSize);