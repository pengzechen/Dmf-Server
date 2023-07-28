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

#include <dm_bind_cpu.h>

static int cpu_processer = 0;

void cpu_init() {
    cpu_processer = sysconf(_SC_NPROCESSORS_CONF);
}

void cpu_bind(int i) {
    cpu_set_t mask;
    cpu_set_t get;
    printf("worker: %d, bind cpu: %d\n", i, i);
    CPU_ZERO(&mask);
    CPU_SET(i,&mask);
    if(sched_setaffinity(0,sizeof(cpu_set_t),&mask) == -1)
    {
        printf("warning: could not set CPU affinity, continuing...\n");
    }
}