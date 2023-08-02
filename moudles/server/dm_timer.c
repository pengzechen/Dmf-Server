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

#include <dm_timer.h>

static timer_min_heap_t *heap;


static void min_heap_push( timer_event_t *event) {
    int i = heap->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap->events[p]->timeout <= event->timeout) break;
        heap->events[i] = heap->events[p];
        i = p;
    }
    heap->events[i] = event;
}

static timer_event_t* min_heap_top() {
    return heap->events[0];
}

static void min_heap_pop() {
    timer_event_t *event = heap->events[--heap->size];
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int a = i * 2 + 1, b = i * 2 + 2;
        if (b < heap->size && heap->events[b]->timeout < heap->events[a]->timeout) a = b;
        if (heap->events[a]->timeout >= event->timeout) break;
        heap->events[i] = heap->events[a];
        i = a;
    }
    heap->events[i] = event;
}

void handle_events() {
    time_t current_time = time(NULL);
    timer_event_t *event;
    while( heap->size>0 ) {
        if(heap->size > 4096*128) printf("error");
        if (heap->events[0]->flag == 1 ) {  // flag
            event = min_heap_top(heap);
            min_heap_pop(heap);
            free(event);
        } else if( heap->events[0]->flag == 0 && heap->events[0]->timeout <= current_time ){
            event = min_heap_top(heap);
            min_heap_pop(heap);
            event->callback();
            free(event);   
        } else {    // haven't time out
            break;
        }
    }
}

void add_timer( int timeout, void (*callback)(), timer_event_t* event) {
    event->timeout = time(NULL) + timeout;
    event->callback = callback;
    min_heap_push(event);
}


void timer_init() {
    heap = (timer_min_heap_t*)malloc(sizeof(timer_min_heap_t));
	heap->size = 0;
}


/* test function start*/
static void print_current_time() {
    time_t current_time = time(NULL);
    printf("Current time: %s", ctime(&current_time));
}

extern int test_timer() {
    timer_init();

    for(int i=0; i<20; i++) {
        timer_event_t *event = (timer_event_t *)malloc(sizeof(timer_event_t));
        event->flag = 1;
        add_timer(5, print_current_time, event);
    }

    while (true) {
        printf("handle events...\n");
        handle_events();
        sleep(1);
    }
    return 0;
}