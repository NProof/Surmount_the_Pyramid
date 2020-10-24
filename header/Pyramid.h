#ifndef PYRAMID_H_INCLUDED
#define PYRAMID_H_INCLUDED

struct Pyramid {
    int n;
    char mapOfPyramid[15][15][15];
};

void readData(struct Pyramid *, FILE *);
void printMap(struct Pyramid *);

#endif // PYRAMID_H_INCLUDED
