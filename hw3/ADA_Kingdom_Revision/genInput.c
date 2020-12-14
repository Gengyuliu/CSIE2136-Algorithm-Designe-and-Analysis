#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 100
#define MAX2 1000000000
#define MAX3 30000000000000

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
    int u, v, d;
    int n = (int)randnum(1, MAX1); 
    printf("%d\n", n);
    for (i = 0; i < n-1; ++i){ 
        printf("%", randnum(1, MAX2));
    }
    printf("\n");
    for (i = 0; i < M; ++i){
        u = (int)randnum(1, N);
        while((v = (int)randnum(1,N)) == u){;}
         
        printf("%d %d %lld\n", u, v, randnum(0,MAX2));
    }
    return 0;
}
