/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 16:41:31
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 16:55:47
 * @FilePath: /桌面/GITHUB/Linux/高级IO/14-7.c
 * @Description: 死锁例子
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/type.h>
#include<system/stat.h>
#include"test.h"

static void lockabyte(const char *name,int fd,off_t offset)
{
    if(lock_reg(fd,F_SETLK,F_WRLCK,offset,SEEK_SET,1)<0)
        perror("write _lock error");
    printf("%s:got the lock,byte %lld\n",name,(long long)offset);
}

int main(void)
{
    int fd;
    pid_t pid;

    if((fd=creat("templock",FILE_MODE))<0)
        perror("creat error");
    if(write(fd,"ab",2)!=2)
        perror("write error");

    
}