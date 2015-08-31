#include <stdio.h>
#include "udpsocklib.h"

int main()
{
    //sendPacket("127.0.0.1", "4950", "Hello");
    //testFunction();
    char *results;
    int *size;
    int error = 0;
    while (error == 0)
    {
        error = listenForPacket("4950", results, size);
        //results = malloc(sizeof(char)*(*size));
       // printf("packet recieved with data: %s\n", results);
    }
    return 0;
    
}