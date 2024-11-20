#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdbool.h>

typedef void *Type;
typedef struct Queue *Queue;

void initializeQueue(Queue* q);
void enqueue(Queue* q, volatile unsigned int * value);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void dequeue(Queue* q);
int peek(Queue* q);
void printQueue(Queue* q);

#endif