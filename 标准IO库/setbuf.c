#include<stdio.h>

int main()
{

}

void my_setbuf(FILE *restrict fp, char *restrict buf)
{
    if(buf == NULL)
    {
        setvbuf(fp,buf,_IONBF,0);
        printf("no buf\n");
        exit(0);
    }
    else
    {
        if(fp == stderr)
        {
            if(setvbuf(fp,buf,_IONBF,0)!=0)
            {
                perror("setvbuf error\n");
                exit(-1);
            }
            printf("stderr is no buf\n");
        }
        else
        {
            if(setvbuf(fp,buf,_IOLBF,BUFSIZ)!=0)
            {
                perror("setvbuf error\n");
                exit(-1);
            }
            printf("Line buf\n");
        }    
    }
}