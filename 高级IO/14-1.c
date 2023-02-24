/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 15:51:24
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 16:04:11
 * @FilePath: /桌面/GITHUB/Linux/高级IO/14-1.c
 * @Description: 
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

char buf[500000];

void set_fl(int fd,int flags)
{
    int old;
    if((old=fcntl(fd,F_GETFD,0))==-1)
        perror("fcntl F_GETFD error");
    old |= flags;
    if(fcntl(fd,F_SETFD,old)<0)
        perror("fcntl F_SETFD error");
}

void clr_fl(int fd,int flags)
{
    int old;
    if((old=fcntl(fd,F_GETFD,0))==-1)
        perror("fcntl F_GETFD error");
    old &= ~flags;
    if(fcntl(fd,F_SETFD,old)<0)
        perror("fcntl F_SETFD error");
}

int main(void)
{
    int ntowrite,nwrite;
    char *ptr;
    ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
    fprintf(stderr,"read %d bytes\n",ntowrite);

    set_fl(STDOUT_FILENO,O_NONBLOCK);

    ptr=buf;
    while(ntowrite>0)
    {
        errno=0;
        nwrite=write(STDOUT_FILENO,ptr,ntowrite);
        fprintf(stderr,"nwrite=%d,errno=%d\n",nwrite,errno);

        if(nwrite>0)
        {
            ptr+=nwrite;
            ntowrite-=nwrite;
        }
    }

    clr_fl(STDOUT_FILENO,O_NONBLOCK);
    exit(0);
}

