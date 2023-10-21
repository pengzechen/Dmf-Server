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


#ifndef __DM_TIMER_INCLUDE__
#define __DM_TIMER_INCLUDE__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Timer Timer;

struct Timer {
    time_t          expire;
    void            (*callback)();
    Timer*          next;
};

#ifdef __cplusplus
extern "C" {
#endif
    void heapify();
    void addTimer(Timer* newTimer, int expire, void (*callback)());
    void deleteTimer(Timer* target);
    void executeTimers();

#ifdef __cplusplus
}           /* end of the 'extern "C"' block */
#endif


#endif // __DM_TIMER_INCLUDE__