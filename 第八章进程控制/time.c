#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/times.h>

static void pr_times(clock_t,struct tms *,struct tms *);
static void do_cmd(char *);

void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination , exit status = %d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n",WTERMSIG(status),
#ifdef  WCOREDUMP
            WCOREDUMP(status)?"(core file generated)":"");
#else
        "");
#endif
/*
#ifdef 指令必须由#endif 指令关闭。

#ifdef 用法的一般格式为：

#ifdef 宏名
程序段1
#else
程序段2
#endif

它的意思是，如果当前的宏已被定义过，则对“程序段1”进行编译，否则对“程序段2”进行编译。
*/
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(int argc,char *argv[])
{
    int i;
    setbuf(stdout,NULL);
    for(i=1;i<argc;i++)
    do_cmd(argv[i]);
    exit(0);
}

static void do_cmd(char *cmd)
{
    struct tms tmssart,tmsend;
    clock_t start,end;
    int status;

    printf("\ncommand:%s\n",cmd);

    if((status = times(&tmssart))==-1)
        perror("times error");
    if((status=system(cmd))<0)
        perror("system error");
    if((status = times(&tmsend))==-1)
        perror("times error");

    pr_times(end-start,&tmssart,&tmsend);
    pr_exit(status);
}


static void pr_times(clock_t real,struct tms *tmsstart,struct tms *tmsend)
{
    static long clktck = 0;
    if(clktck==0)
        if((clktck=sysconf(_SC_CLK_TCK))<0)
            perror("sysconf error");
    
    printf(" real:%7.2f\n",real / (double)clktck);
    printf(" user:%7.2f\n",(tmsend->tms_utime-tmsstart->tms_utime)/(double)clktck);
    printf(" sys:%7.2f\n",(tmsend->tms_stime-tmsstart->tms_stime)/(double)clktck);
    printf(" child user:%7.2f\n",(tmsend->tms_cutime-tmsstart->tms_cutime)/(double)clktck);
    printf(" child sys:%7.2f\n",(tmsend->tms_cstime-tmsstart->tms_cstime)/(double)clktck);

}