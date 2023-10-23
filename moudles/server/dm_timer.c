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
#include <dm_server_config.h>
#include <string.h>


static Timer* heap = NULL;

void heapify() {
    Timer* parent = heap;
    Timer* current = heap->next;
    while (current != NULL) {
        if (current->expire < parent->expire) {
            Timer* temp = current;
            parent->next = current->next;
            current = parent->next;
            temp->next = heap;
            heap = temp;
        } else {
            parent = current;
            current = current->next;
        }
    }
}


void deleteTimer(Timer* target) {
    if (heap == NULL || target == NULL) {
        return;
    }
    if (heap == target) {
        Timer* temp = heap;
        heap = heap->next;
        return;
    }
    Timer* parent = heap;
    Timer* current = heap->next;
    while (current != NULL && current != target) {
        parent = current;
        current = current->next;
    }
    if (current == NULL) {
        return;
    }
    parent->next = current->next;
    heapify();
}



void addTimer(Timer* newTimer, int expire, void (*callback) ()) {

    newTimer->callback = callback;
	newTimer->expire = time(NULL) + expire;
	newTimer->next = NULL;

    if (heap == NULL) {
        heap = newTimer;
    } else {
        Timer* temp = heap;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTimer;
    }

    heapify();
}

void executeTimers() {
    time_t now = time(NULL);
    req_t* req = NULL;
    Timer* timer;

    while (heap != NULL && heap->expire <= now) {
        timer = heap;
        heap = heap->next;
        
        req = container_of(timer, req_t, timer_event);

        req->timer_event.callback();
        
        timer = NULL;
    }
}
