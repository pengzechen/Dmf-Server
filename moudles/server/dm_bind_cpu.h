/* 
    *  Copyright 2023 Ajax
    *
    *  Licensed under the Apache License, Version 2.0 (the "License");
    *  you may not use this file except in compliance with the License.
    *
    *  You may obtain a copy of the License at
    *
    *    http://www.apache.org/licenses/LICENSE-2.0
    *    
    *  Unless required by applicable law or agreed to in writing, software
    *  distributed under the License is distributed on an "AS IS" BASIS,
    *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    *  See the License for the specific language governing permissions and
    *  limitations under the License. 
    *
    */

#ifndef __DM_BIND_CPU_INCLUDE__
#define __DM_BIND_CPU_INCLUDE__

#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/resource.h>


#ifdef __cplusplus
extern "C" {
#endif

extern int ulimit();
extern void cpu_init();
extern void cpu_bind(int i);


#ifdef __cplusplus
}		/* end of the 'extern "C"' block */
#endif

// int sc_nprocessor_conf = sysconf(_SC_NPROCESSORS_CONF);
// int sc_nprocessor_onln = sysconf(_SC_NPROCESSORS_ONLN);
// printf("sc_nprocessor_conf[%d]\n", sc_nprocessor_conf);
// printf("sc_nprocessor_onln[%d]\n", sc_nprocessor_onln);

// int a = 0;
// cpu_set_t mask;// cpu核的集合
// cpu_set_t get;// 获取在集合中的cpu
// printf("this is: %d\n",a);// 打印这是第几个线程
// CPU_ZERO(&mask);// 将集合置为空集
// CPU_SET(a,&mask);// 设置亲和力值

// if(sched_setaffinity(0,sizeof(cpu_set_t),&mask)==-1)// 设置线程cpu亲和力
// {
//     printf("warning: could not set CPU affinity, continuing...\n");
// }

#endif  // __DM_BIND_CPU_INCLUDE__