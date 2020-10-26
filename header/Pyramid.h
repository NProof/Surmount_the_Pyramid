#ifndef PYRAMID_H_INCLUDED
#define PYRAMID_H_INCLUDED

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Pyramid.h"

struct Pyramid {
    int n;
    int nodes;
    char mapOfPyramid[15][15][15];
};

void readData(struct Pyramid *, FILE *);
void printMap(struct Pyramid *);

#endif // PYRAMID_H_INCLUDED
