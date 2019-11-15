#include <stdio.h>
#include <time.h>
#include <string.h>

int main(void)
{
    printf("Content-Type: text/plain;charset=us-ascii\n\n");
    printf("Hello world\n");
    printf("time: %u\n", (unsigned)time(NULL));
    return 0;
}