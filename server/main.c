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

#include <dm_server.h>
#include <dm_master.h>

#define MYTYPE(x) _Generic((x), \
    int: "int",                 \
    float: "float",             \
    double: "double",           \
    test_t: "test_t"            \
)

typedef struct test_t {
    int a;
    char b;
} test_t ;

int main(int arg, char* args[]) {
/*
    // type compare
    test_t ss;
    printf("%s \n", MYTYPE(ss));
    // transform force
    test_t* obj = (test_t*)malloc(sizeof(test_t));
    obj->a = 1;
    int* a = (int*)malloc(sizeof(int));
    a = (int*)obj;
    printf("%d\n", *a);
    free(obj);  // attention to double free
*/

    int serfd = create_socket( SERVER_PORT );
	// start_server(serfd);
    epoll_ssl_server(serfd);

    // master_start_multi_process_server();
    
	return 0;
}