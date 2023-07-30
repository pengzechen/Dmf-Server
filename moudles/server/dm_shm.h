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

#ifndef __DM_SHM_INCLUDE__
#define __DM_SHM_INCLUDE__

#include <stdatomic.h>
#include <sys/shm.h>
#include <stdio.h>              //perror

typedef struct shm_data_t {
    atomic_int accept_mutex;
    _Atomic int accept_num;
    _Atomic int read_num;
    _Atomic int write_num;
    _Atomic int close_num;
} shm_data_t ;


#ifdef __cplusplus
extern "C" {
#endif


extern shm_data_t* create_get_shm(int name);



#ifdef __cplusplus
}		/* end of the 'extern "C"' block */
#endif


#endif  // __DM_SHM_INCLUDE__