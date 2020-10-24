#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "../header/Pyramid.h"

int printMap(struct Pyramid * pyramid, int n) {
    int l = 0, k = 0, j = 0;
    int i = 0;
    while (n-2*l>0) {
        putchar(pyramid->mapOfPyramid[l][k+l][j+l]);
        ++j;
        if (j>=n-2*l) {
            j = 0;
            ++k;
            if (k>=n-2*l) {
                k = 0;
                ++l;
                if(n-2*l>0)
                    putchar('\n');
            }
            putchar('\n');
        }
        else putchar(' ');
        ++i;
    }
    return i;
}

int readData(struct Pyramid * pyramid, char * fileName) {
    FILE * fp;
    char line[256];

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "file open error\n");
        exit(EXIT_FAILURE);
    }

    int level = 0;
    int j = 0;
    int i = 0;
    int n = 0;

    if (fgets(line, sizeof(line), fp)!=NULL) {
        char linetmp[50];
        strcpy(linetmp, line);
        char * token = strtok(linetmp, " \t\n");
        char tmp[15]={'\0'};
        while(token != NULL) {
            strcpy(tmp+i, token);
            pyramid->mapOfPyramid[level][j+level][i+level] = tmp[i];
            token = strtok(NULL, " \t\n");
            ++i;
        }
    }
    n = i;
    if (n==0)
        exit(EXIT_FAILURE);
    i = 0;
    ++j;
    while (fgets(line, sizeof(line), fp)!=NULL) {
        char linetmp[50];
        strcpy(linetmp, line);
        char * token = strtok(linetmp, " \t\n");
        char tmp[15]={'\0'};
        while(token != NULL) {
//            printf("%d, %d, %d)\n", level, j, i);
            strcpy(tmp+i, token);
            pyramid->mapOfPyramid[level][j+level][i+level] = tmp[i];
            token = strtok(NULL, " \t\n");
            ++i;
            if (i>=n-2*level) {
                i = 0;
                ++j;
                if (j>=n-2*level) {
                    j = 0;
                    ++level;
                }
            }
        }
    }

    fclose(fp);
    return n;
}
