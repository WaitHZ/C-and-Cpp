#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
typedef int Position;

typedef struct {
    ElementType *stackArr;
    Position top;
    int capacity;
} Stack;

Stack *makeNewStack(int size) {
    Stack *newStack;

    newStack = (Stack*)malloc(sizeof(Stack));
    newStack->top = -1;
    newStack->stackArr = (ElementType*)malloc(sizeof(ElementType)*size);
    newStack->capacity = size;

    return newStack;
}

bool isEmptyStack(Stack *s) {
    return s->top == -1;
}

bool isFullStack(Stack *s) {
    return s->top + 1 == s->capacity;
}

void push(Stack *s, ElementType val) {
    if(!isFullStack(s)) {
        (s->stackArr)[++s->top] = val;
    }
    else {
        printf("Stack is full!\n");
        abort();
    }
}

ElementType pop(Stack *s) {
    if(isEmptyStack(s)) {
        printf("Stack is empty!\n");
        abort();
    }
    
    return (s->stackArr)[(s->top)--];
}

ElementType getTopEle(Stack *s) {
    if(isEmptyStack(s)) {
        printf("Stack is empty!\n");
        abort();
    }
    
    return (s->stackArr)[s->top];
}

void freeStack(Stack *s) {
    free(s->stackArr);
    free(s);
}

#endif