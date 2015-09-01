/*
 ** talker.c -- a datagram "client" demo
 */

#include "udpsocklib.h"

int main()
{
    
    sendPacket("127.0.0.1", "10599", "message contents");
    return 0;
}