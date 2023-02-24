/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 16:33:13
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 16:46:35
 * @FilePath: /桌面/GITHUB/Linux/高级IO/14-6.c
 * @Description: 测试一个锁条件函数:如果存在一把锁，他阻塞由参数指定的锁请求，则此函数返回持有这边现有锁的进程的进程ID，否则函数返回0
 * 
 */
#include"test.h"

pid_t lock_test(int fd,int type,off_t offset,int whence, off_t len)
{
    struct flock lock;
    lock.l_type=type;
    lock.l_start=offset;
    lock.l_len=len;
    lock.l_whence=whence;

    if(fcntl(fd,F_GETLK,&lock)<0)
        perror("fcntl error");
    
    if(lock.l_type==F_UNLCK)
        return(0);/*false,region isn`t locked by another proc*/
    
    return(lock.l_pid);/*true,return pid of lock owner*/
}