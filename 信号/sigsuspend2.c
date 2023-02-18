/*
 * @Author: Adward
 * @Email: 1654783946@qq.com
 * @Date: 2023-02-17 17:21:30
 * @LastEditors: Adward
 * @LastEditTime: 2023-02-17 18:39:57
 * @FilePath: /桌面/GITHUB/Linux/信号/sigsuspend2.c
 * @Description: 
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

volatile sig_atomic_t quitflag;
//volatile 变量是随时可能发生变化的，每次使用时都需要去内存里重新读取它的值,与volatile变量有关的运算，不要进行编译优化，以免出错
//sig_atomic_t 当把变量声明为该类型是，则会保证该变量在使用或赋值时， 无论是在32位还是64位的机器上都能保证操作是原子的， 它会根据机器的类型自动适应。
static void sig_int(int signo)
{
    if(signo==SIGINT)
        printf("\ninterrupt\n");
    if(signo==SIGQUIT)
        quitflag=1;
}

int main(viod)
{
    sigset_t oldmask,newmask,zeromask;

    if(signal(SIGINT,sig_int)==SIG_ERR)
        perror("signal (SIGINT) error");
    if(signal(SIGQUIT,sig_int)==SIG_ERR)
        perror("signal (SIGQUIT) error");
    
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        perror("SIG_BLOCK error");
    
    while(!quitflag)
        sigsuspend(&zeromask);  /*在sigsuspend函数执行期间，不管之前的信号屏蔽集，使用sigsuspend函数参数的屏蔽集，直至函数执行完毕。相当于信号屏蔽集暂时被替换。在此函数执行之后信号屏蔽字设置为调佣它之前的值.*/
    
    quitflag = 0;

    exit(0);
}