#include <stdio.h>

int main(void)
{
    printf("Content-Type: text/html;charset=us-ascii\n\n");
    printf("<form action=\"viewdata.cgi\"><div><input type=\"submit\" value=\"View\"></div></form>");
    return 0;
}