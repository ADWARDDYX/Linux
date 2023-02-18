/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-17 16:15:03
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-17 16:32:57
 * @FilePath: /桌面/GITHUB/Linux/线程属性/12_4.c
 * @Description:线程属性detachstate   ----  线程分离
 * 
 */
#include<sdio.h>
#include<stdlib.h>
#include<pthread.h>

int makethread(void *(*fn)(void *),void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;

    err=pthread_attr_init(&attr);
    if(err!=0)
        return(err);
    err=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if(err==0)
        err=pthread_create(&tid,&attr,fn,arg);
    pthread_attr_destroy(&attr); 
    return(err);
}