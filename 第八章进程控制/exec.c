#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

char *env_init[]={"USER=unknow","PATH=/temp",NULL};
int main(void)
{
    pid_t pid;

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
    {
        if(execle("/home/adward/桌面/Linux/Linux_new/第八章进程控制/echoall","test","myarg1","MY ARG2",(char *)0,env_init)<0)
            perror("execle error");
    }

    if(waitpid(pid,NULL,0)<0)
        perror("waitpid error");

    putenv("PATH=/home/adward/桌面/Linux/Linux_new/第八章进程控制/");
    if((pid=fork())<0)
        perror("fork error");
    else if(pid == 0)
    {
        if(execlp("echoall","test","only 1 arg",(char *)0)<0)
            perror("execlp error");
    }
}