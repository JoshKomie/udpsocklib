//example usage

#include <stdio.h>
#include "udpsocklib.h"

int main()
{
    char *results, *sender;
    while (1)
	{
		listenForPacketAndSource("10599", &results, &sender);
        printf("received packet with data %s from address %s\n", results, sender);
		sendPacket(sender, "10599", results);
	}
    
    return 0;
    
}