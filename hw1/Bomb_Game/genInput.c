#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 100000
#define MAX2 1000000000
#define MAX3 10000

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
    int N = (int)randnum(1, MAX1);
    int M = (int)randnum(1, MAX1);
    int event;
    int c, d;
    int l, r, p, k;

    printf("%d %d\n", N, M);
    for (i = 0; i < M; i++){
        event = (int)randnum(0, 1); 
        switch(event){
            case 0:
                c = (int)randnum(1, N);
                d = (int)randnum(1, MAX2);
                printf("%c %d %d\n", 'P', c, d);
                break;
            case 1:
                r = (int)randnum(1, N);
                l = (int)randnum(1, (ll)r);
                p = (int)randnum(1, MAX2);
                k = (int)randnum(1, MAX3); 
                printf("%c %d %d %d %d\n", 'A', l, r, p, k);
                break;
        }
    }

    return 0;
}
