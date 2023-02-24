/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-19 17:31:49
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-19 17:42:17
 * @FilePath: /桌面/GITHUB/Linux/高级IO/14-24.c
 * @Description: readn 和 writen函数
 * 
 */
#include"test.h"

ssize_t readn(int fd, void *ptr,size_t n)
{
    size_t nleft;
    ssize_t nread;

    nleft = n;
    while(nletf>0)
    {
        if((nread=read(fd,ptr,nleft))<0)
        {
            if(nleft == n)
                return(-1);
            else
                break;
        }
        else if(nread==0)
            break;
        
        nleft-=nread;
        ptr+=nread;
    }
    return(n-nleft);
}

ssize_t writen(int fd,const void *ptr,size_t n)
{
    size_t nleft;
    ssize_t nwritten;

    nleft = n;
    while(nleft>0)
    {
        if((nwritten=write(fd,ptr,nleft))<0)
        {
            if(nleft==n)
            {
                return(-1);
            }
            else
                break;
        }
        else if(nwritten==0)
            break;
        
        nleft-=nwritten;
        ptr+=nwritten;
    }

    return(n-nleft);
}
