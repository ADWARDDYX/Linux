#include<stdio.h>
#include<stdlib.h>

void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebuffered(FILE *);
int buffer_size(FILE *);

int main()
{
    FILE *fp;
    fputs("enter any character \n",stdout);
    if(getchar()==EOF)
        perror("getchar error");
    fputs("one line to standard error \n",stderr);

    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);

    if((fp = fopen("/etc/passwd","r")) == NULL)
        perror("fopen error");
    if(getc(fp) == EOF)
        perror("getc error");
    pr_stdio("/etc/passwd",fp);
    exit(0);
}

void pr_stdio(const char *name , FILE *fp)
{
    printf("stream = %s, ",name);
    if(is_unbuffered(fp))
        printf("unbuffered");/*不带缓冲*/
    else if(is_linebuffered(fp))
        printf("line bufferec");/*行缓冲*/
    else 
        printf("fuly buffered");/*全缓冲*/
    
    printf(", buffer size = %d\n", buffer_size(fp));
}

int is_unbuffered(FILE *fp)
{
    return (fp->_flags & _IONBF);
}

int is_linebuffered(FILE *fp)
{
    return (fp->_flags & _IOLBF);
}

int buffer_size(FILE *fp)
{
        return (BUFSIZ);
}
