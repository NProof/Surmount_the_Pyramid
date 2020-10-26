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

struct listNode * constructorListNode(struct Node * node, struct listNode * list) {
    struct listNode * ptrObj = (struct listNode *)malloc(sizeof(struct listNode));
    ptrObj->node = node;
    ptrObj->next = list;
    return ptrObj;
}

struct Maze * constructorMaze(struct Pyramid * pmd) {
    struct Maze * maze = (struct Maze *)malloc(sizeof(struct Maze));
    maze->n = pmd->n;
    maze->nodes = pmd->nodes;
    maze->arrNodes = (struct Node *)malloc(sizeof(struct Node) * maze->nodes);
    for(int i=0; i<maze->nodes; ++i) {
        int j = -1, k = -1, l = -1;
        linearToPmd(i, maze->n, &j, &k, &l);
        maze->arrNodes[i].index = i;
        maze->arrNodes[i].type = pmd->mapOfPyramid[l][k][j];
        maze->arrNodes[i].inAdj = NULL;
        maze->arrNodes[i].outAdj = NULL;
    }
    for(int i=0; i<maze->nodes; ++i) {
        char type = maze->arrNodes[i].type;
        int j, k ,l;
        linearToPmd(i, maze->n, &j, &k, &l);
        if (type != 'X') {
            int toI;
            if (pmdToLinear(&toI, maze->n, j, k + 1, l) && maze->arrNodes[toI].type != 'X') {
                struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                maze->arrNodes[toI].inAdj = newList;
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }
            if (pmdToLinear(&toI, maze->n, j, k - 1, l) && maze->arrNodes[toI].type != 'X') {
                struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                maze->arrNodes[toI].inAdj = newList;
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }
            if (pmdToLinear(&toI, maze->n, j + 1, k, l) && maze->arrNodes[toI].type != 'X') {
                struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                maze->arrNodes[toI].inAdj = newList;
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }
            if (pmdToLinear(&toI, maze->n, j - 1, k, l) && maze->arrNodes[toI].type != 'X') {
                struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                maze->arrNodes[toI].inAdj = newList;
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }
            if ( (type == 'U' || type == 'P') && pmdToLinear(&toI, maze->n, j, k, l + 1)
                && maze->arrNodes[toI].type != 'X') {
                if(maze->arrNodes[toI].type == 'D') {
                    struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                    struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                    maze->arrNodes[toI].inAdj = newList;
                }
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                struct listNode *newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }

            if ((type == 'D' || type == 'P') && pmdToLinear(&toI, maze->n, j, k, l - 1)
                && maze->arrNodes[toI].type != 'X') {
                if(maze->arrNodes[toI].type == 'U') {
                    struct listNode * crrIn = maze->arrNodes[toI].inAdj;
                    struct listNode * newList = constructorListNode(&maze->arrNodes[i], crrIn);
                    maze->arrNodes[toI].inAdj = newList;
                }
                struct listNode * crrOut = maze->arrNodes[i].outAdj;
                struct listNode *newList = constructorListNode(&maze->arrNodes[toI], crrOut);
                maze->arrNodes[i].outAdj = newList;
            }
        }
    }
    return maze;
}

void destroyMaze(struct Maze * maze) {
    for(int i=0; i<maze->nodes; ++i) {
        struct listNode * crrIn = maze->arrNodes[i].inAdj;
        while (crrIn != NULL) {
            struct listNode * tmp = crrIn;
            crrIn = crrIn->next;
            free(tmp);
        }
        struct listNode * crrOut = maze->arrNodes[i].outAdj;
        while (crrOut != NULL) {
            struct listNode * tmp = crrOut;
            crrOut = crrOut->next;
            free(tmp);
        }
    }
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

struct Path * newPath(int l, struct Node * node, struct Path * link) {
    struct Path * p = (struct Path *)malloc(sizeof(struct Path));
    p->len = l;
    p->node = node;
    p->link = link;
}

void addContain(struct containerLN ** barr, struct Path * p) {
    struct containerLN * tmp = *barr;
    *barr = (struct containerLN *)malloc(sizeof(struct containerLN));
    (*barr)->obj = p;
    (*barr)->pre = tmp;
}

void clearContain(struct containerLN ** barr) {
    while ((*barr) != NULL) {
        struct containerLN * tmp = (*barr);
        *barr = tmp->pre;
        free(tmp->obj);
        free(tmp);
    }
}

int findS(struct Maze * maze) {
    for(int i=0; i<maze->nodes; ++i) {
        if (maze->arrNodes[i].type == 'S')
            return i;
    }
    return -1;
}

int findF(struct Maze * maze) {
    for(int i=0; i<maze->nodes; ++i) {
        if (maze->arrNodes[i].type == 'F')
            return i;
    }
    return -1;
}

struct Path * shortestPath(struct Maze * maze, int s, int f) {
    struct containerLN * barr = NULL;
    struct Path * p = newPath(0, &maze->arrNodes[s], NULL);
    addContain(&barr, p);
    PQnode * pq = newNode(p, p->len);
    while (! isEmpty(&pq)) {
        p = peek(&pq);
        pop(&pq);
        if (p->node->index == f)
            break;
        struct listNode * outNodes = p->node->outAdj;
        while (outNodes != NULL) {
            struct Node * toNode = outNodes->node;
            bool cyclic = false;
            struct Path * backpath = p;
            while (backpath != NULL) {
                if(toNode == backpath->node) cyclic = true;
                backpath = backpath->link;
            }
            if(cyclic) {
                outNodes = outNodes->next;
                continue;
            }
            struct Path * nPath = newPath(p->len + (toNode->type == 'T' ? 3 : 1), toNode, p);
            addContain(&barr, nPath);
            push(&pq, nPath, nPath->len);
            outNodes = outNodes->next;
        }
    }

    int l = p->len;
    struct Path * path = NULL;
    struct Path * tmp = path;
    struct Node * node;
    while (p != NULL) {
        tmp = path;
        path = (struct Path *)malloc(sizeof(struct Path));
        path->link = tmp;
        path->node = p->node;
//        path->len = p->len;
        p = p->link;
    }
    path->len = l;

    while (! isEmpty(&pq)) pop(&pq);
    free(pq);
    clearContain(&barr);
    return path;
}

struct Path * shortestPathRange(struct Maze * maze, int s, int f, int * ptr_n) {
    int n = 0;
    struct containerLN * barr = NULL;
    struct Path * p = newPath(0, &maze->arrNodes[s], NULL);
    addContain(&barr, p);
    PQnode * pq = newNode(p, p->len);
    while (! isEmpty(&pq)) {
        p = peek(&pq);
        pop(&pq);
        if (p->node->index == f)
            break;
        struct listNode * outNodes = p->node->outAdj;
        while (outNodes != NULL) {
            struct Node * toNode = outNodes->node;
            bool cyclic = false;
            struct Path * backpath = p;
            while (backpath != NULL) {
                if(toNode == backpath->node) cyclic = true;
                backpath = backpath->link;
            }
            if(cyclic) {
                outNodes = outNodes->next;
                continue;
            }
            struct Path * nPath = newPath(p->len + (toNode->type == 'T' ? 3 : 1), toNode, p);
            addContain(&barr, nPath);
            push(&pq, nPath, nPath->len);
            outNodes = outNodes->next;
        }
    }

    int l = p->len;
    struct Path * path = NULL;
    struct Path * tmp = path;
    struct Node * node;
    while (p != NULL) {
        tmp = path;
        path = (struct Path *)malloc(sizeof(struct Path));
        path->link = tmp;
        path->node = p->node;
        p = p->link;
    }
    path->len = l;

    n = 1;
    while (! isEmpty(&pq)) {
        p = peek(&pq);
        pop(&pq);
        if (p->len > l+5)
            break;
        ++n;
        struct listNode * outNodes = p->node->outAdj;
        while (outNodes != NULL) {
            struct Node * toNode = outNodes->node;
            bool cyclic = false;
            struct Path * backpath = p;
            while (backpath != NULL) {
                if(toNode == backpath->node) cyclic = true;
                backpath = backpath->link;
            }
            if(cyclic) {
                outNodes = outNodes->next;
                continue;
            }
            struct Path * nPath = newPath(p->len + (toNode->type == 'T' ? 3 : 1), toNode, p);
            addContain(&barr, nPath);
            push(&pq, nPath, nPath->len);
            outNodes = outNodes->next;
        }
    }
    *ptr_n = n;

    while (! isEmpty(&pq)) pop(&pq);
    free(pq);
    clearContain(&barr);
    return path;
}

void colorMaze(struct Maze * maze, struct Path * path) {
    if(path != NULL) {
        struct Path * cur = path;
        while (cur != NULL) {
            cur->node->type = '*';
            cur = cur->link;
        }
    }
    else printf("No path\n");
}
