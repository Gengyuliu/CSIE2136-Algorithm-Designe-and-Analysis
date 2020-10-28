#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//#define MAX1 5000
//#define MAX2 10
//#define MAX3 1000000000
#define MAX1 500000
#define MAX2 1000 
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
    int N = (int)randnum(2, MAX1); 
    int K = (int)randnum(1, MAX1);
    printf("%d %d\n", N, K);
    
    for (i=0; i < N; ++i){
        printf("%d ", (int)randnum(1, MAX3));
    }
    printf("\n"); 
    return 0;
}
