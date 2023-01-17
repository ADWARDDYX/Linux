#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int mydup2(int fd, int fd2)
{
    int fd_min, index, n, t, *fdarr;
    if((fd_min = dup(fd)) < 0){
        perror("error when dup");
        return -1;
    }
    if(fd_min == fd2)
        return fd_min;
    if(fd_min > fd2){
        printf("fd2 has being used");
        close(fd2);
        fd_min=dup(fd);
        return fd_min;
    }
    n = fd2 - fd_min + 1;
    fdarr = (int *)malloc(n * sizeof(int));
    fdarr[0] = fd_min;
    index = 1;
    while(index < n){
        if((fdarr[index] = dup(fd)) < 0){
            perror("error when dup");
            return -1;
        }
        if(fdarr[index] == fd2){
            for(int i = 0; i <= index - 1; i++)
                close(fdarr[i]);
            t = fdarr[index];
            free(fdarr);
            return t;
        }
        index++;
    }
    perror("error when loop");
    return -1;
}