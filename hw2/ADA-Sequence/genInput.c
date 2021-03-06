#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 200
#define MAX2 600
#define MAX3 100

typedef long long ll;

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
    int K = (int)randnum(1, MAX2);
    int D = (int)randnum(0, 0);
    //int K = 0;
    //int D = 0;
    printf("%d %d %d\n", N, K, D);
    for (i = 0; i < N; ++i){
        printf("%d ", (int)randnum(1, MAX3));
    }
    printf("\n");
    for (i = 0; i < N; ++i){
        printf("%d ", (int)randnum(1, MAX2));
    }
    printf("\n");
    for (i = 0; i < N; ++i){
        printf("%d ", (int)randnum(1, 3));
    }
    printf("\n");
    return 0;
}
