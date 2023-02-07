#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>

int main(void)
{
    system("ps(l)");
    exit(0);
}