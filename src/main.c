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

//        printMap(&pyramid);

        int j, k, l;
        for(int i = 0; i < pyramid.nodes; ++i) {
            linearToPmd(i, pyramid.n, &j, &k, &l);
//            printf(" %2d -> ( %2d, %2d, %2d )", i, l, k ,j);
            int tmp = -1;
            pmdToLinear(&tmp, pyramid.n, j, k, l);
//            printf(" -> %2d\n", tmp);
            if(i != tmp)
                printf("FAILED in %d\n", i);
        }

        int pass = 0;
        for(j = 0; j < pyramid.n; ++j) {
            for(k = 0; k < pyramid.n; ++k) {
                for(l = 0; l < pyramid.n; ++l) {
                    int tmp = -1;
                    if(pmdToLinear(&tmp, pyramid.n, j, k, l)==true) {
                        ++pass;
//                        printf("( %2d, %2d, %2d ) -> %2d\n", l, k, j, tmp);
                    }
                }
            }
        }
        if (pass!=pyramid.nodes)
            printf("FAILED");
    }
}
