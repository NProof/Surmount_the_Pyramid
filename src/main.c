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

        printf("======\n%s\n\n", argv[i]);

        readData(&pyramid, fp);
        fclose(fp);

        struct Maze * maze = constructorMaze(&pyramid);

        int s = findS(maze);
        int f = findF(maze);
        struct listNode * path = shortestPath(maze, s, f);
//
        if(path != NULL) {
            struct Path * cur = path;
            printf("%d", cur->node->index);
            while (cur->link != NULL) {
                cur = cur->link;
                printf(" -> %d", cur->node->index);
            }
            printf(" $\n");
        }
        else printf("No Way to F\n");

        printMaze(maze);
        destroyMaze(maze);
    }
}
