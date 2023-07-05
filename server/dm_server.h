
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


#ifndef __DM_SERVER_INCLUDE__
#define __DM_SERVER_INCLUDE__

#include <dm_server_config.h>
#include <dm_threading_pool.h>
#include <dm_events.h>

#define SERVER_PORT 8080
#define EPOLL_MAX_EVENT_NUM 1024
#define EPOLL_FD_NON_BLOCKING
#define EPOLL_WAIT_TIMEOUT 100


struct arg_t {
	int serfd;
	thread_pool_t* ptr_thread_pool;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void* server_make();
extern void  dmf_server_show_info();
extern void  start_server();
extern void  start_multi_threading_server();


#ifdef __cplusplus
}		/* end of the 'extern "C"' block */
#endif


#endif  // __DM_SERVER_INCLUDE__