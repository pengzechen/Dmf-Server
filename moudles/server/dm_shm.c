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

#include <dm_shm.h>

shm_data_t* create_get_shm(int name) {

    void* shm = NULL;
    shm_data_t* shared;

    int shm_fd;
    shm_fd = shmget((key_t)name, sizeof(shm_data_t), 0666|IPC_CREAT);
    if(shm_fd == -1) {
        perror("shmget");
    }
    shm = shmat(shm_fd, 0, 0);
    if(shm == (void*)-1) {
        perror("shmat");
    }

    shared = (shm_data_t*)shm;

    return shared;

}