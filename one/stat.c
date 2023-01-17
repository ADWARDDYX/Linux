#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>

int main()
{
    int fd = open("1.txt",O_RDONLY);

    struct stat buf;

    fstat(fd,&buf);
    
    printf("uid_t:%d",buf.st_mode);

}