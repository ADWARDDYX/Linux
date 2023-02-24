/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 16:28:32
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 16:31:23
 * @FilePath: /桌面/GITHUB/Linux/高级IO/14-5.c
 * @Description: 
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>


int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flcok lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd,cmd,&lock));
}