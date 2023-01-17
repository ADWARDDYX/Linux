#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void ser_fl(int fd, int flags)  /*flags are file status flags to turn on*/
{
    int val;
    /*set zhuang tai miao su fu */
    if((val=fcntl(fd, F_GETFL,0))<0)
        perror("fcntl  F_GETFL error");

    val |= flags;/*turn on flags*/
    if((val=fcntl(fd, F_SETFL,val))<0) 
        perror("fcntl F_SETFL error");       
}

void clr_fl(int fd, int flags)  /*flags are file status flags to turn on*/
{
    int val;
    /*set zhuang tai miao su fu */
    if((val=fcntl(fd, F_GETFL,0))<0)
        perror("fcntl  F_GETFL error");

    val &= ~flags;/*turn flags off*/
    if((val=fcntl(fd, F_SETFL,val))<0) 
        perror("fcntl F_SETFL error");       
}