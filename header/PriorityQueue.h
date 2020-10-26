#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#include "Maze.h"

typedef struct PriorityQueueNode {
    int priority;
    struct Path * data;
    struct PriorityQueueNode * next;
} PQnode;

void push(PQnode **, struct Path *, int);

PQnode * newNode(struct Path * d, int p);

struct Path * peek(PQnode **);

void pop(PQnode **);

int isEmpty(PQnode **);

#endif // PRIORITYQUEUE_H_INCLUDED
