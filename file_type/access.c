#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc ,char *argv[])
{
    if(argc != 2)
    {
        perror("usage:access <pathname>");
    }

    if(access(argv[1],R_OK)<0)
    {
        perror("access error");
    }
    else
        printf("read access ok\n");
    
    if(open(argv[1],O_RDONLY)<0)
        perror("OPEN ERROR");
    else 
        printf("open for reading OK\n");
    
    exit(0);
}