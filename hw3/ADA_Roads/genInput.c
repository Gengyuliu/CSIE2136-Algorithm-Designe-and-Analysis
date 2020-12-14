#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 50
#define MAX2 10
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
    int M = (int)randnum(1, MAX1);
    //int S = (int)randnum(1, N);
    //int T = (int)randnum(S+1, N);
    int S = 1;
    int T = N;
    printf("%d %d %d %d\n", N, M, S, T);
    for (i = 0; i < M; ++i){
        u = (int)randnum(1, N);
        v = (int)randnum(1, N);
        while(v == u)
            v = (int)randnum(1, N);
        printf("%d %d %lld\n", u, v, (ll)1);
        //printf("%d %d %lld\n", u, v, randnum(0,MAX2));
    
    }
    return 0;
}
