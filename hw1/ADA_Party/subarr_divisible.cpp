/*	Brute force approach O(N^3)	*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
using namespace std;
typedef long long ll;

void prefixSum(int *a, ll *p, int N){
    int i;
    p[0] = 0;
    
    for (i = 1; i <= N; i++){
        p[i] = p[i-1] + a[i];
    }
    return;    
}


ll divisible_subarr(ll *p, int N, int *mod, int K){
    int i;
    int idx;
    ll cnt = 0;
    memset(mod, 0, K);
    for (i = 0; i < N; i++){
        idx = p[i]%K;
        mod[idx] += 1;
    }
    
    for (i = 0; i < K; i++){
        if (mod[i] > 1){
            cnt += (mod[i]*(mod[i]-1))>>1;
        }
    }
    return cnt;
}

int main(int argc, char *argv[])
{
    int i;
    int N, K;
    ll cnt;
    scanf("%d", &N);
    scanf("%d", &K);

    int *a      = (int*)malloc((N+1)*sizeof(int));
    ll  *p      = (ll*)malloc((N+1)*sizeof(ll));
    int *mod    = (int*)malloc(K*sizeof(int));
    a[0] = 0;
    for (i = 1; i <= N; i++){
        scanf("%d", &a[i]);
    }
    
    prefixSum(a, p, N);
    cnt = divisible_subarr(p, N, mod, K);
    printf("%lld\n", cnt); 
    return 0;
}
