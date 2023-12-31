
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


#ifndef __DM_SERVER_CONFIG_INCLUDE__
#define __DM_SERVER_CONFIG_INCLUDE__

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <dm_shm.h>
#include <dm_timer.h>

typedef enum _lis_type_s {
    HTTP = 1, 
    HTTPS, 
    HTTP_PROXY,
    HTTPS_PROXY,
    TCP_PROXY,
} lis_type_t;

#define TIMER_YES 'Y'
#define TIMER_NO  'N'

typedef struct _req_t {
    int                         fd;
    int                         efd;
    lis_type_t                  type;
    void                  *     data;
    SSL                   *		ssl;
    shm_data_t            *     sd;
    
    Timer                       timer_event;
    char                        timer;
} req_t;


#define container_of(ptr, type, member) (type *) ((unsigned char *) (ptr) - offsetof(type, member))

typedef struct _listen_info_s {
	char                        ip[64];
	int                         port;
	int                         fd;
	lis_type_t                  type;
} lis_inf_t;


#define SERVER_DEFAULT_PORT 8080

#define SERVER_DEBUG

#define WORKER_NUM 56

#define SERVER_MAX_LISTEN_NUM 10


#endif  // __DM_SERVER_CONFIG_INCLUDE__