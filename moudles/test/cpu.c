#include <stdlib.h>
#include <stdio.h>
// #include <sys/types.h>
#define __USE_GNU  
// #include <sys/sysinfo.h>
#include <unistd.h>

#define __USE_GUN
// #include <sched.h>
// #include <ctype.h>
#include <string.h>
#include <pthread.h>
#define THREAD_MAX_NUM 100// 1个cpu内最多进程数
int num=0; //cpu中核数

void* threadFun(void* arg)// arg传递线程标号，自己定义
{
    //sleep(2);
    cpu_set_t mask;// cpu核的集合
    cpu_set_t get;// 获取在集合中的cpu
    int* a=(int*)arg;
    printf("this is: %d\n",*a);// 打印这是第几个线程
    CPU_ZERO(&mask);// 将集合置为空集
    CPU_SET(*a,&mask);// 设置亲和力值
    
    if(sched_setaffinity(0,sizeof(cpu_set_t),&mask)==-1)// 设置线程cpu亲和力
    {
        printf("warning: could not set CPU affinity, continuing...\n");
    }
    while(1)
    {
        CPU_ZERO(&get);
        if(sched_getaffinity(0,sizeof(get),&get)==-1)// 获取线程cpu亲和力
        {
            printf("warning: could not get thread affinity, continuing...\n");
        }
        for(int i=0;i<num;++i)
        {
            if(CPU_ISSET(i,&get))// 判断线程与哪个cpu有亲和力
            {
                //printf("this thread %d is running processor: %d\n",i,i);
                int a=1000000*1000000;
            }
        }
    }
    return NULL;
}

int main(void)
{
    num=sysconf(_SC_NPROCESSORS_CONF);// 获取核数
    pthread_t thread[THREAD_MAX_NUM];
    printf("system has %i processor(s).\n",num);
    int tid[THREAD_MAX_NUM];
    for(int i=0;i<10;++i)
    {
        if(i%2==0)
        {
            tid[i]=i;// 每个线程必须有个tid[i]
            pthread_create(&thread[i],NULL,threadFun,(void*)&tid[i]);
        }
        //sleep(2);
    }
    for(int i=0;i<num;++i)
    {
        pthread_join(thread[i],NULL);
    }
    return 0;
}