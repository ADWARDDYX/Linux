#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
    struct stat buf;
    /* turn off roup-execute and turn on set-group-ID*/
    if(stat("foo_1.txt",&buf)<0)
        perror("stat foo_1.txt error");
    if(chmod("foo_1.txt",(buf.st_mode&~S_IXGRP)|S_ISGID)<0)
        perror("chmod error");
    
    /*set absolute mode to "rw-r--r--"*/

    if(stat("foo_2.txt",&buf)<0)
        perror("stat foo_2.txt error");
    if(chmod("foo_2.txt",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)<0)
        perror("chmod error");
    
    exit(0);
}
