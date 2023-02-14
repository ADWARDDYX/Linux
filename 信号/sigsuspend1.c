/*
 * @Author: ADward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-12 17:12:13
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-14 16:30:45
 * @FilePath: /桌面/GITHUB/Linux/信号/sigsuspend1.c
 * @Description: 
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save=errno;

    if(sigprocmask(0,NULL,&sigset)<0)
        perror("sigprocmask error");
    else{
        printf("%s",str);
        if(sigismember(&sigset,SIGINT))
            printf(" SIGINT");
        if(sigismember(&sigset,SIGQUIT))
            printf(" SIGOUIT");
        if(sigismember(&sigset,SIGUSR1))
            printf(" SIGUSR1");
        if(sigismember(&sigset,SIGALRM))
            printf(" SIGALRM");

        printf("\n");
    }

    errno = errno_save;
}
static void sig_int(int);

int main(void)
{   
    sigset_t newmask,oldmask,waitmask;

    pr_mask("program start: ");
    if(signal(SIGINT,sig_int)==SIG_ERR)
        perror("signal(SIGINT) error");
    sigemptyset(&waitmask);
    sigaddset(&waitmask,SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);


    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        perror("SIG_BLOCK error");

    pr_mask("in critical region");

    if(sigsuspend(&waitmask)!=-1)
        perror("sigsuspend error");

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        perror("SIG_SETMASK error");

    pr_mask("program exit: ");

    exit(0); 
}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int:");
}