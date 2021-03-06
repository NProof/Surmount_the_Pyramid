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

struct Path {
    int len;
    struct Node * node;
    struct Path * link;
} ;

struct Path * newPath(int l, struct Node * node, struct Path * link);

struct containerLN {
    struct Path * obj;
    struct containerLN * pre;
};

void addContain(struct containerLN ** barr, struct Path * p);
void clearContain(struct containerLN ** barr);

int findS(struct Maze *);
int findF(struct Maze *);

struct Path * shortestPath(struct Maze *, int, int);

void colorMaze(struct Maze *, struct Path *);

#endif // MAZE_H_INCLUDED
