#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc,char*argv[])
{
    int val;
    if(argc!=2)
    {
        perror("usage:a.out <descriptor>#");
    }

    if((val = fcntl(atoi(argv[1]), F_GETFL ,0))<0)
        perror("fcntl error");
    
    switch (val & O_ACCMODE)
    {
    case O_RDONLY:
        /* code */
        printf("read only");
        break;
    case O_WRONLY:
        /* code */
        printf("write only");
        break;
    case O_RDWR:
        /* code */
        printf("read write");
        break;
    default:
        printf("unknown access mode");
        break;
    }

    if(val&O_APPEND)
        printf(", append");
    if(val&O_NONBLOCK)
        printf(", nonblocking");
    if(val&O_SYNC)
        printf(", synchronous writes");
    
#if !defined(_POSIX_C_SOURCE)&&defined(O_FSYNC)&&(O_FSYNC != O_SYNC) 
    if(val&O_FSYNC)
        printf(", synchronous writes");
#endif 
    putchar('\n');
    exit(0);
}