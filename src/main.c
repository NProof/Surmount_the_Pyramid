#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../header/Pyramid.h"
#include "../header/Maze.h"

int main(int argc, char ** argv) {
    FILE * fp;
    struct Pyramid pyramid;
    for (int i=1; i<argc; ++i) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "file open error\n");
            exit(EXIT_FAILURE);
        }

        printf("=== %s ===\n", argv[i]);

        readData(&pyramid, fp);
        fclose(fp);

        struct Maze * maze = constructorMaze(&pyramid);

        int s = findS(maze);
        int f = findF(maze);
        struct Path * path = shortestPath(maze, s, f);

        colorMaze(maze, path);
        printf("Path length : %d\n\n", path->len);
        printMaze(maze);

        destroyMaze(maze);
    }
}
