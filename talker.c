/*
 ** talker.c - example usage
 */

#include "udpsocklib.h"

int main()
{
    
    sendPacket("127.0.0.1", "10599", "message contents");
    return 0;
}