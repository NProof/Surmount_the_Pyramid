#include "../header/Maze.h"

bool linearToPmd(int i, int n, int *out_j, int *out_k, int *out_l) {
    int sq = n;
    int l = 0;
    while (sq*sq <= i) {
        i -= sq*sq;
        sq-=2;
        ++l;
    }
    *out_l = l;
    int k = l;
    while (sq <= i) {
        i -= sq;
        ++k;
    }
    *out_k = k;
    *out_j = i+l;
    return true;
}

bool pmdToLinear(int *i, int n, int j, int k, int l) {
    int tmp = 0;
    int sh;
    for(sh = 0; sh < l; ++sh) {
        tmp += (n-2*sh)*(n-2*sh);
    }
    if(n<2*sh || k<l || j<l || k-l>=n-2*sh || j-l>=n-2*sh)
        return false;
    tmp += (n-2*sh)*(k-l)+(j-l);
    *i = tmp;
    return true;
}

struct Maze * constructorMaze(struct Pyramid * pmd) {
    struct Maze * maze = (struct Maze *)malloc(sizeof(struct Maze));
    maze->n = pmd->n;
    maze->nodes = pmd->nodes;
    maze->arrNodes = (struct Node *)malloc(sizeof(struct Node) * maze->nodes);
    for(int i=0; i<maze->nodes; ++i) {
        int j = -1, k = -1, l = -1;
        linearToPmd(i, maze->n, &j, &k, &l);
        maze->arrNodes[i].type = pmd->mapOfPyramid[l][k][j];
    }
    return maze;
}

void destroyMaze(struct Maze * maze) {
    free(maze->arrNodes);
    free(maze);
}

void printMaze(struct Maze * maze) {
    int n = maze->n;
    int i = 0;
    while(i<maze->nodes) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                putchar(maze->arrNodes[i].type);
                ++i;
                if(k!=n-1)
                    putchar(' ');
            }
            putchar('\n');
        }
        if(i!=maze->nodes)
            putchar('\n');
        n = n - 2;
    }
    return ;
}
