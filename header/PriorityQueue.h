#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include "Maze.h"

typedef struct PriorityQueueNode {
    int priority;
    struct listNode * data;
    struct PriorityQueueNode * next;
} PQnode;

void push(PQnode **, struct listNode *, int);

PQnode * newNode(struct listNode * d, int p);

struct listNode * peek(PQnode **);

void pop(PQnode **);

int isEmpty(PQnode **);

#endif // PRIORITYQUEUE_H_INCLUDED
