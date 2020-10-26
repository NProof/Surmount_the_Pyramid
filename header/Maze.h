#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

#include "../header/Pyramid.h"

struct Node {
    char type;
};

struct Maze {
    int n;
    int nodes;
    struct Node * arrNodes;
};

struct Maze * constructorMaze(struct Pyramid *);

void printMaze(struct Maze *);

void destroyMaze(struct Maze *);

#endif // MAZE_H_INCLUDED
