#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 4
#define MAX2 100000

typedef long long ll;

/*	random number in [l, r]	*/
ll randnum(ll l, ll u){
    ll num;
    num = (rand() % (u - l + 1)) + l;
}

int main(int argc, char *argv[]){
    srand(time(0));
    int i, j;
    int n = (int)randnum(2, MAX1); 
    int mark;
    //int K = 0;
    //int D = 0;
    printf("%d\n", n);
    for (i = 0; i < n; ++i){
        printf("%d ", (int)randnum(0, MAX2));
    }
    printf("\n"); 
    int flag = (int)randnum(1, 1);
    printf("%d\n", flag);
    return 0;
}
