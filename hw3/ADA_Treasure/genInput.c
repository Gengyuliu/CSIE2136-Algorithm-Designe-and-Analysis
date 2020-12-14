#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 500000
#define MAX2 1000000000
#define MAX3 30

typedef long long ll;

/*	random number in [l, r]	*/
ll randnum(ll l, ll u){
    ll num;
    num = (rand() % (u - l + 1)) + l;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int i;
    int u, v;
    int N = (int)randnum(1, MAX1); 
    int M = (int)randnum(0, MAX1);
    printf("%d %d\n", N, M);
    for (i = 0; i < N; ++i){ 
        printf("%lld ", randnum(1, MAX2));
    }
    printf("\n");
    for (i = 0; i < M; ++i){
        u = (int)randnum(1, N);
        v = (int)randnum(1, N);
        while(u == v){
            v = (int)randnum(1, N);
        }

        printf("%d %d %lld\n", u, v, randnum(0,MAX2));
    }
    return 0;
}
