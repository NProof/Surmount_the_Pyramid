#ifndef PYRAMID_H_INCLUDED
#define PYRAMID_H_INCLUDED

struct Pyramid {
    char mapOfPyramid[15][15][15];
};

int readData(struct Pyramid *, char *);
int printMap(struct Pyramid *, int);

#endif // PYRAMID_H_INCLUDED
