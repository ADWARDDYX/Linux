/*
 * @Author: ADward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-14 16:49:12
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-14 16:56:08
 * @FilePath: /桌面/GITHUB/Linux/线程/11_2.c
 * @Description: 线程创建
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid=getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,(unsigned long)tid,(unsigned long)tid);
}


void *test(void *arg)
{
    printids("new thread: ");
    exit(0);
}
int main()
{
    int err;

    err = pthread_create(&ntid,NULL,test,NULL);
    if(err==-1)
        perror("pthread_creat error");
    printids("main thread: ");
    sleep(1);
    exit(0);
}