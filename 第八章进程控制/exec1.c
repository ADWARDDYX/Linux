#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

char *env_init[]={"USER=unknow","PATH=/temp",NULL};

int main()
{
    pid_t pid;

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
    {
        if(execle("/home/adward/桌面/Linux/Linux_new/第八章进程控制/testinterp","test","myarg1","MY ARG2",(char *)0,env_init)<0)
            perror("execle error");
    }
    if(waitpid(pid,NULL,0)<0)
        perror("waitpid error");
    
    exit(0);
}