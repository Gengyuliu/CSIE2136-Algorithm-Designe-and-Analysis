#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 100000
#define MAX2 400
#define MAX3 1000000000

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
    int A = (int)randnum(0, MAX3);
    int B = (int)randnum(1, N);
    printf("%d %d %d %d\n", N, K, A, B);
    for (i = 0; i < N; ++i){
        printf("%d ", (int)randnum(-MAX3, MAX3));
    }
    
    return 0;
}
