#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void)
{
    if(chdir("/home/adward/桌面/Linux/Linux_new/one")<0)
        perror("chdir failed");
    printf("chdir to / temp succeeded\n");
    exit(0);
}