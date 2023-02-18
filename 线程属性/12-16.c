/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-17 18:37:21
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-17 19:05:55
 * @FilePath: /桌面/GITHUB/Linux/线程属性/12-16.c
 * @Description: 线程和信号章节例题
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;//条件变量

void *thr_fn(void* aarg)
{
    int err,signo;
    for(;;)
    {
        err=sigwait(&mask,&signo);
        if(err!=0)
            perror("sigwait failed");
        
        switch (signo)
        {
        case SIGINT:
            /* code */
            printf("\ninterrupt\n");
            break;
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag=1;
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&waitloc);
            return(0);
        
        default:
            printf("unexpected signal %d\n",signo);
            exit(1);
        }
    }
}

int main(void)
{
    int err;
    sigset_t oldmask;
    pthread_t tid;
    
    sigemptyset(&mask);
    sigaddset(&mask,SIGQUIT);
    sigaddset(&mask,SIGINT);

    if((err=pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0)
        perror("SIG_BLOCK error");
    
    err=pthread_create(&tid,NULL,thr_fn,0);
    if(err!=0)
        perror("can`t create thread");
    
    pthread_mutex_lock(&lock);
    while(quitflag==0)
        pthread_cond_wait(&waitloc,&lock);
    pthread_mutex_unlock(&lock);

    quitflag = 0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
        perror("SIG_SETMASK,error");
    
    exit(0);
}