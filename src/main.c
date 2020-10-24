#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/Pyramid.h"

int main(int argc, char ** argv) {
    for (int i=1; i<argc; ++i) {
        printf("======\n%s\n\n", argv[i]);
        struct Pyramid pyramid;

        int n = readData(&pyramid, argv[i]);
        int nodes = printMap(&pyramid);
    }
}
