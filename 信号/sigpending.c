/*
 * @Description: 函数sigpending的例子
 * @Autor: Adward
 * @Mill: 1654783946@qq.com
 * @Date: 2023-02-07 16:16:49
 * @LastEditTime: 2023-02-07 16:29:29
 * @FilePath: /Linux/Linux_new/信号/sigpending.c
 */
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

static void sig_quit(int signo);

int main(void)
{
    sigset_t newmask,oldmask,pendmask;
    
    if(signal(SIGQUIT,sig_quit)==SIG_ERR)
        perror("signal error");
    
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        perror("sigprocmask error\n");
    
    sleep(5);

    if(sigpending(&pendmask)<0)
        perror("sigpending error");
    if(sigismember(&pendmask,SIGQUIT))
        printf("\nSIGQUIT pending\n");
    
    if(sigprocmask(SIG_UNBLOCK,&oldmask,NULL)<0)
        perror("sigprocmask error");
    printf("SIGQUIT unblocked\n");

    sleep(5);
    exit(0);
}   

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
        perror("can`t reset SIGQUIT");
}