/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 16:43:46
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 17:42:02
 * @FilePath: /桌面/GITHUB/Linux/高级IO/test.h
 * @Description: 
 * 
 */
#ifndef _test_h_
#define _test_h_

#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>

pid_t lock_test(int fd,int type,off_t offset,int whence, off_t len);
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
ssize_t readn(int fd, void *ptr,size_t n);
ssize_t writen(int fd,const void *ptr,size_t n);

#endif