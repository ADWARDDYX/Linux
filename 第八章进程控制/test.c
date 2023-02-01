#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

static void charatatime(char *);

int main()
{
    pid_t pid;

    if((pid=fork())<0)
        perror("fork error");
    else if(pid == 0)
        charatatime("output from child\n");
    else
        charatatime("utput from parent\n");
    
    exit(0);
}

static void charatatime(char *str)
{
    char *ptr;
    int c;
    
    setbuf(stdout,NULL); /*设置缓冲类型*/
    for(ptr = str;(c=*ptr++)!=0;)
        putc(c,stdout);
}