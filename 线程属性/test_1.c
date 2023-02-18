/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-18 17:28:05
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-18 18:46:56
 * @FilePath: /桌面/GITHUB/Linux/线程属性/test_1.c
 * @Description: 
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare(void)
{
    int err;
    printf("preparing locks..\n");
    if((err=pthread_mutex_lock(&lock1))!=0)
        perror("can`t lock lock1 in prepare");
    if((err=pthread_mutex_lock(&lock2))!=0)
        perror("can`t lock lock2 in prepare");
}

void parent(void)
{
    int err;
    printf("parent unlocking locks..\n");
    if((err=pthread_mutex_unlock(&lock1))!=0)
        perror("can`t unlock lock1 in parent handler");
    if((err=pthread_mutex_unlock(&lock2))!=0)
        perror("can`t unlock lock2 in parent handler");
}

void child(void)
{
    int err;
    printf("child unlocking locks..\n");
    if((err=pthread_mutex_unlock(&lock1))!=0)
        perror("can`t unlock lock1 in parent handler");
    if((err=pthread_mutex_unlock(&lock2))!=0)
        perror("can`t unlock lock2 in parent handler");
}

void *thr_fn(void *arg)
{
    printf("thread stared...\n");
    pause();
    return(0);
}

int main(void)
{
    int err;
    pid_t pid;
    pthread_t tid;

    if((err=pthread_atfork(prepare,parent,child))!=0)
        perror("can`t install fork handlers");
    if((err=pthread_create(&tid,NULL,thr_fn,NULL))!=0)
        perror("can`t create thread");
    sleep(2);
    printf("parent about to fork..\n");

    if((pid=fork())<0)
    {
        perror("fork error");
    }
    else if(pid == 0)
        printf("child returned form fork\n");
    else 
    {
        printf("parent returned from fork\n");
    }
        
    
    exit(0);
}