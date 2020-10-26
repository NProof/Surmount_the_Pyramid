#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#include "../header/Pyramid.h"

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

#endif // MAZE_H_INCLUDED
