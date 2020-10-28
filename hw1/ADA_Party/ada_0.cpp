/*	Brute force approach O(N^3)	*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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

ll rangeSum(ll *p, int N, int l, int r){
    if (l > r || r >= N || l <0)
        return -1;
    return p[r] - p[l-1];
}

int max(int *a, int l, int r){
    int i, a_max = -1<<31;
    for(i = l; i <= r; i++){
        if (a[i] >  a_max)
            a_max = a[i];
    }
    return a_max;
}

int min(int *a, int l, int r){
    int i, a_min = 1<<30;
    for(i = l; i <= r; i++){
        if (a[i] <  a_min)
            a_min = a[i];
    }
    return a_min;

}

ll numPair(int *a, ll *p, int N, int K){
    int l, r;
    ll cnt = 0;
    ll a_max, a_min;
    ll tot;
    for(l = 1; l <= N; l++){
        for (r = l+1; r <= N; r++){
            a_max = (ll)max(a, l, r);   //O(r-l)
            a_min = (ll)min(a, l, r);   //O(r-l)
            tot = p[r] - p[l-1] - a_max - a_min;
            if (tot%K == 0)
               cnt++; 
        }
    }
    return cnt;
}

int main(int argc, char *argv[])
{
    int i;
    int N, K;
    ll num_pair;
    scanf("%d", &N);
    scanf("%d", &K);

    int *a = (int*)malloc((N+1)*sizeof(int));
    ll  *p = (ll*)malloc((N+1)*sizeof(ll));
    a[0] = 0;
    for (i = 1; i <= N; i++){
        scanf("%d", &a[i]);
    }
    
    prefixSum(a, p, N);
    num_pair = numPair(a, p, N, K);
    printf("%lld\n", num_pair); 
    return 0;
}
