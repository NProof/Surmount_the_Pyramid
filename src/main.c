#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Pyramid.h"

int main(int argc, char ** argv) {
    FILE * fp;
    for (int i=1; i<argc; ++i) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "file open error\n");
            exit(EXIT_FAILURE);
        }
        printf("======\n%s\n\n", argv[i]);
        struct Pyramid pyramid;

        readData(&pyramid, fp);
        fclose(fp);
        printMap(&pyramid);
    }
}
