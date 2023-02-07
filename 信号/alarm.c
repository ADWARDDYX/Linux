/*
 * @Description: 
 * @Autor: Adward
 * @Mill: 1654783946@qq.com
 * @Date: 2023-02-07 14:23:08
 * @LastEditTime: 2023-02-07 14:30:44
 * @FilePath: /Linux/Linux_new/信号/alarm.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<signal.h>

static void my_alarm(int signo)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if((rootptr=getpwnam("root"))==NULL)
        perror("getpwnam(root) error");
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;

    signal(SIGALRM,my_alarm);
    alarm(1);
    for(;;)
    {
        if((ptr=getpwnam("sar"))==NULL)
            perror("getpwnam error");
        if(strcmp(ptr->pw_name,"sar")!=0)
            printf("return value corrupted!, pw_name = %s\n",ptr->pw_name);
    }

    exit(0);
}