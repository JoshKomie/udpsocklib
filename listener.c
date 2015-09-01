//example usage

#include <stdio.h>
#include "udpsocklib.h"

int main()
{
    char *results;
    int *size;
    listenForPacket("10599", &results);
   
    printf("received packet with data %s", results);
    return 0;
    
}