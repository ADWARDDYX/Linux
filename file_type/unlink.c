#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{

    if(unlink("/home/adward/桌面/Linux/Linux_new/file_type/foo/testdir")<0)
        perror("unlink error");
    printf("file unlinked\n");
    exit(0);
}