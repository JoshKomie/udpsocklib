/*
 ** talker.c - example usage
 */

#include "udpsocklib.h"

int main()
{
    
    sendPacket("localhost", "10599", "message contents");
    return 0;
}