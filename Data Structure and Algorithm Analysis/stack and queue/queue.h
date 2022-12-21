#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef int ElementType;
typedef int Position;

typedef struct {
    ElementType *queueArr;
    Position head, tail;
    int capacity;
} Queue;

Queue *makeNewQueue(int size) {
    Queue *newQueue;

    newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->queueArr = (ElementType*)malloc(sizeof(ElementType)*(size+1));
    newQueue->capacity = size + 1;
    newQueue->head = newQueue->tail = 0;

    return newQueue;
}

bool isEmptyQueue(Queue *q) {
    return (q->head % q->capacity) == (q->tail % q->capacity);
}

bool isFullQueue(Queue *q) {
    return (q->head % q->capacity) == ((q->tail+1) % q->capacity);
}

void enQueue(Queue *q, ElementType val) {
    if(isFullQueue(q)) {
        printf("Queue is full!\n");
        abort();
    }

    (q->queueArr)[(++(q->tail))%(q->capacity)] = val;
}

ElementType deQueue(Queue *q) {
    if(isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        abort();
    }

    return (q->queueArr)[(++(q->head))%(q->capacity)];
}

ElementType getHeadEle(Queue *q) {
    if(isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        abort();
    }

    return (q->queueArr)[q->head%q->capacity];
}

int elementNumInQueue(Queue *q) {
    int eleNum;
    
    if(q->tail%q->capacity > q->head%q->capacity) {
        eleNum = q->tail%q->capacity - q->head%q->capacity;
    }
    else if(q->tail%q->capacity == q->head%q->capacity) {
        eleNum = 0;
    }
    else {
        eleNum = q->tail%q->capacity - q->head%q->capacity + q->capacity-1;
    }

    return eleNum;
}

void freeQueue(Queue *q) {
    free(q->queueArr);
    free(q);
}

#endif