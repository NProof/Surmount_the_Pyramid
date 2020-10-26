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
