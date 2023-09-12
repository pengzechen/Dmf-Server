#include "timer2.h"

Timer* heap = NULL;

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

void addTimer(time_t expire, void (*callback)()) {
    Timer* newTimer = (Timer*)malloc(sizeof(Timer));
    newTimer->expire = time(NULL) + expire;
    newTimer->callback = callback;
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
    while (heap != NULL && heap->expire <= now) {
        Timer* timer = heap;
        heap = heap->next;
        timer->callback();
        free(timer);
    }
}


