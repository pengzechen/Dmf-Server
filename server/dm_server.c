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


void* server_make(void* arg) {
	
	struct arg_t args = *(struct arg_t*)arg;
	int serfd = args.serfd;
	thread_pool_t* threadPool1 = args.ptr_thread_pool;

	int epoll_fd = epoll_create(100);
	
	struct epoll_event ev;
    struct epoll_event evs[ EPOLL_MAX_EVENT_NUM ];

#ifdef EPOLL_FD_NON_BLOCKING
	if( set_non_blocking(epoll_fd) == -1) {
		perror("epoll set non blocking ");
	}
#endif // EPOLL_FD_NON_BLOCKING

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = serfd;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serfd, &ev);

	int evnum = 0;
	int tempfd;
	struct epoll_event tempev;

	
	for(;;) {
		evnum = epoll_wait(epoll_fd, evs, EPOLL_MAX_EVENT_NUM, EPOLL_WAIT_TIMEOUT);
		if(evnum == -1){
			perror("epoll wait");
			continue;
		}
		for(int i=0; i<evnum; i++) {
			
			if ((evs[i].events & EPOLLHUP)||(evs[i].events & EPOLLERR)) {
				printf("------------------------\n");
				handle_close(evs[i].data.fd, epoll_fd);
				
			} else if( evs[i].data.fd == serfd ) {
				handle_accept(serfd, epoll_fd);
				// addTask(threadPool1, serfd, epoll_fd, 1);

			} else if( evs[i].events & EPOLLIN ) {
				handle_read(evs[i].data.fd, epoll_fd);
				// addTask(threadPool1, evs[i].data.fd, epoll_fd, 2);

			} else if( evs[i].events & EPOLLOUT ) {
				handle_write(evs[i].data.fd, epoll_fd);
				// addTask(threadPool1, evs[i].data.fd, epoll_fd, 3);

			} else {
				printf("unknow events\n");
			}
		}
	}
	close(serfd);
	close(epoll_fd);
}


void dmf_server_show_info() {

	printf("Dmfserver Moule version:0.0.2\n\n");


	printf("|--------SERVER CONFIGURE--------\n");
	printf("|PORT:%d\n", SERVER_PORT);
	printf("|MAX_EVENT:%d\n", EPOLL_WAIT_TIMEOUT);

}


void start_server() {
	int serfd = create_socket( SERVER_PORT );

	struct arg_t args;
	thread_pool_t threadPool1;
	thread_pool_init(&threadPool1, 1);
	args.serfd = serfd;
	args.ptr_thread_pool = &threadPool1;

	server_make((void*)(&args));

}


void start_multi_threading_server() {
	int serfd = create_socket( SERVER_PORT );

	struct arg_t args;
	thread_pool_t threadPool1;
	thread_pool_init(&threadPool1, 4);
	args.serfd = serfd;
	args.ptr_thread_pool = &threadPool1;

	server_make((void*)(&args));
	for (int k = 0; k < 1; ++k) {
		pthread_t roundCheck;
		pthread_create(&roundCheck, NULL, server_make, (void*)(&args));
		pthread_join(roundCheck, NULL);
	}
}