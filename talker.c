/*
 ** talker.c - example usage
 */

#include "udpsocklib.h"

int main()
{
    
    sendPacket("127.0.0.1", "10599", "message contents");
	char *data;
	listenForPacket("10599", &data);
	printf("Response received: %s\n", data);
    return 0;
}