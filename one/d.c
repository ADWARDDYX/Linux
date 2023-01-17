#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    char buf[4096];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buf,4096,stdin)!=NULL)
    {
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]=0;
        if((pid=fork())<0)
            perror("fork error");
        else if(pid==0)
        {
            execlp(buf,buf,(char *)0);
            exit(127);
        }

        if((pid=waitpid(pid,&status,0))<0)
            perror("waitpid error");
        printf("%% ");
    }
    exit(0);
}