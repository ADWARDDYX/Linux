#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
    pid_t pid;

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
    {
        if(execl("/home/adward/桌面/Linux/Linux_new/第八章进程控制/testinterp","testinterp","myarg1","MY ARG2",(char *)0)<0)
            perror("execl error");
    }
    if(waitpid(pid,NULL,0)<0)
        perror("waitpid error");
    
    exit(0);
}