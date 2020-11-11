#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 200000
#define MAX2 200000
#define MAX3 30000000000000

typedef long long ll;
typedef struct Segment{
    int idx;
    int L;
    int R;
    ll  W;
}Segment;
/*	random number in [l, r]	*/
ll randnum(ll l, ll u){
    ll num;
    num = (rand() % (u - l + 1)) + l;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int i, j;
    int N = (int)randnum(1, MAX1); 
    int M = (int)randnum(1, MAX2);
    ll K  = randnum(0, MAX3*MAX1);
    printf("%d %d %lld\n", N, M, K);
    Segment *S = (Segment*)malloc(N*sizeof(Segment)); 
    for (i = 0; i < N; ++i){
        S[i].idx = i;
        S[i].L = (int)randnum(0,M);
        S[i].R = (int)randnum(S[i].L+1,M);
        S[i].W = (ll)randnum(1, MAX3);
        printf("%d %d %lld\n", S[i].L, S[i].R, S[i].W);
    }
    return 0;
}
