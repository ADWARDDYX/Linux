#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;    /*automatic variable onthe stack*/
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1)
        perror("write error");
    printf("befor fork\n"); /*we don`t flush stout*/

    if((pid=fork())<0)
    {
        perror("fork error");
    }
    else if(pid==0)
    {
        globvar++;
        var++;
    }else{
        sleep(2);
    }

    printf("pid = %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);
    exit(0);
}