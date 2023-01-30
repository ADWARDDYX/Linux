#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination , exit status = %d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),
#ifdef  WCOREDUMP
            WCOREDUMP(status)?"(core file generated)":"");
#else
        "");
#endif
/*
#ifdef 指令必须由#endif 指令关闭。

#ifdef 用法的一般格式为：

#ifdef 宏名
程序段1
#else
程序段2
#endif

它的意思是，如果当前的宏已被定义过，则对“程序段1”进行编译，否则对“程序段2”进行编译。
*/
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void)
{
    pid_t pid;
    int status;

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
        exit(7);
    if(wait(&status)!=pid)
        perror("wait eroor");
    pr_exit(status);

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
        abort();
    if(wait(&status)!=pid)
        perror("wait eroor");
    pr_exit(status);

    if((pid=fork())<0)
        perror("fork error");
    else if(pid==0)
        status /= 0;
    if(wait(&status)!=pid)
        perror("wait eroor");
    pr_exit(status);

    exit(0);
}