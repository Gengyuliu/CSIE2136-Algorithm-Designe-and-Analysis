#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 500
#define MAX2 500
#define MAX3 1000000000

typedef long long ll;

/*	random number in [l, r]	*/
ll randnum(ll l, ll u){
    ll num;
    num = (rand() % (u - l + 1)) + l;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    //fp = fopen("input", "w");
    srand(time(0));
    int i, j;
    int n = (int)randnum(1, MAX1); 
    int m = (int)randnum(1, MAX1);
    int k = (int)randnum(0, MAX2);
    int c = (int)randnum(1, MAX3);
    printf("%d %d %d %d\n", n, m, k, c);
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            printf("%d ", (int)randnum(-MAX3, MAX3));
        }
        printf("\n");
    } 
    
    return 0;
}
