#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 200000
#define MAX2 1000000000

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
    int N = (int)randnum(2, MAX1);
    int x, y;
    printf("%d\n", N);
    for (i = 0; i < N; i++){
        x = (int)randnum(0, MAX2);
        y = (int)randnum(0, MAX2); 
        printf("%d %d\n", x, y);
    }

    return 0;
}
