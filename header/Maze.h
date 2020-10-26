#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#include "Pyramid.h"
#include "PriorityQueue.h"

struct Node {
    int index;
    char type;
    struct listNode * inAdj;
    struct listNode * outAdj;
};

struct listNode {
    struct Node * node;
    struct listNode * next;
};

struct Maze {
    int n;
    int nodes;
    struct Node * arrNodes;
};

struct listNode * constructorListNode(struct Node *, struct listNode *);

struct Maze * constructorMaze(struct Pyramid *);

void printMaze(struct Maze *);

void destroyMaze(struct Maze *);

typedef struct Path {
    int len;
    struct Node * node;
    struct Path * link;
} path;

path * newPath(int l, struct Node * node, struct Path * link);

struct containerLN {
    struct Path * obj;
    struct containerLN * pre;
};

void addContain(struct containerLN ** barr, struct Path * p);
void clearContain(struct containerLN ** barr);

int findS(struct Maze *);
int findF(struct Maze *);

struct listNode * shortestPath(struct Maze *, int, int);

#endif // MAZE_H_INCLUDED
