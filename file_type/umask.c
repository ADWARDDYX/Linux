#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH)

int main()
{
    umask(0);
    if(creat("foo_1.txt",RWRWRW)<0)
        perror("creat error");
    
    umask(S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);/**/
    if(creat("foo_2.txt",RWRWRW)<0)
        perror("creat error");
    exit(0);
}