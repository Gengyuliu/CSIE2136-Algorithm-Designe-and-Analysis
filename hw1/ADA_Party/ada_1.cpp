/*	Good-pair (l,r) :=  1 <= l < r <= N and
 *	(sum(l,r) - max(l,r) - min(l,r))modK = 0	*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;

typedef long long ll;

typedef struct Entry{
    int Min = 1<<30;
    int Max = -(1<<30);
}Entry;


/*	unset the array in Memory -> O(2*v.size())	*/
void unset(vector<int> &v, ll *arr){
    int i;
    for (i = 0; i < v.size(); i++){
        arr[v[i]]--;
    }
    v.clear();
    return;
}

int Mod(ll x, int m){
    return ((x%m) + m)% m;
}

void prefixSum(int *a, ll *p, int N){
    int i;
    p[0] = 0;
    for (i = 1; i <= N; i++){
        p[i] = p[i-1] + a[i];
    }
    return;
}


ll Cross(int *a, ll *p, int N, ll *mod, int K, int l, int m, int r){
    int i, j, j1, j2;
    int n_l = m - l + 1;
    int n_r = r - m;
    int rmd;
    int rmd_trgt;
    Entry *L = (Entry*)malloc((n_l+1)*sizeof(Entry));
    Entry *R = (Entry*)malloc((n_r+1)*sizeof(Entry));
    ll cnt = 0;
    vector<int> rmd_idx;

    /*	O(N)	*/   
    /*	left subarray max&min starting from m	*/ 
    L[0].Min = -1<<30, L[0].Max = 1<<30;
    L[n_l].Min = a[m], L[n_l].Max = a[m];
    for (i = n_l-1; i > 0; i--){
        L[i].Min = (a[l+i-1] < L[i+1].Min)?a[l+i-1]:L[i+1].Min;
        L[i].Max = (a[l+i-1] > L[i+1].Max)?a[l+i-1]:L[i+1].Max;
    }
    /*	right subarray max&min starting from m	*/ 
    R[0].Min = a[m+1], R[0].Max = a[m+1];
    R[n_r].Min = -1<<30, R[n_r].Max = 1<<30;
    for (j = 1; j < n_r; j++){
        R[j].Min = (a[m+1+j] < R[j-1].Min)?a[m+1+j]:R[j-1].Min;
        R[j].Max = (a[m+1+j] > R[j-1].Max)?a[m+1+j]:R[j-1].Max;
    }
   
    //memset(mod, 0, K*sizeof(mod));
    /* #1 :	min in left , max in left	*/
    for(i = n_l, j = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Max + (ll)L[i].Min)%K; 
       
        /*	set threshold 	*/
        for(; j < n_r; ){
            if (L[i].Min <= R[j].Min && L[i].Max >= R[j].Max){
                rmd = p[m+1+j]%K;
                ++mod[rmd];
                ++j;
            }
            else
                break;
        }
        cnt += mod[rmd_trgt];
    }
    for(i = n_l, j = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Max + (ll)L[i].Min)%K; 
        for(; j < n_r; ){
            if (L[i].Min <= R[j].Min && L[i].Max >= R[j].Max){
                rmd = p[m+1+j]%K;
                --mod[rmd];
                ++j;
            }
            else
                break;
        }
    }

    //memset(mod, 0, K*sizeof(mod)); 
    /* #2 :	min in left, max in right	*/
    for (i = n_l, j1 = 0, j2 = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Min)%K;  
        /*	maintain the window 	*/ 
        for (; j1 < n_r;){
            if (R[j1].Min >= L[i].Min){  //include this j1
                if (j2 <= j1){
                    ++mod[(p[m+1+j1] - (ll)R[j1].Max)%K];
                }
                
                ++j1;
            }
            else
                break;
        }
        for (; j2 < n_r; ){   //till r[j2].Max > l[i].Max
            if (R[j2].Max <= L[i].Max){ //exclude this j2
                if (j2 < j1){
                    --mod[(p[m+1+j2] - (ll)R[j2].Max)%K];
                }
                ++j2;
            }
            else 
                break;
        }   
        cnt += mod[rmd_trgt];
    }
    for (i = n_l, j1 = 0, j2 = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Min)%K;  
        /*	maintain the window 	*/ 
        for (; j1 < n_r;){
            if (R[j1].Min >= L[i].Min){  //include this j1
                if (j2 <= j1){
                    --mod[(p[m+1+j1] - (ll)R[j1].Max)%K];
                }
                
                ++j1;
            }
            else
                break;
        }
        for (; j2 < n_r; ){   //till r[j2].Max > l[i].Max
            if (R[j2].Max <= L[i].Max){ //exclude this j2
                if (j2 < j1){
                    ++mod[(p[m+1+j2] - (ll)R[j2].Max)%K];
                }
                ++j2;
            }
            else 
                break;
        }   
    }

    /*	#3 : max in left, min in right	*/
    for (i = n_l, j1 = 0, j2 = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Max)%K;
        /*	maintain the window	*/
        for (; j1 < n_r;){
            if (R[j1].Max <= L[i].Max){
                if (j2 <= j1){
                    ++mod[(p[m+1+j1] - (ll)R[j1].Min)%K];
                }
                ++j1;
            }
            else
                break;
        }

        for (; j2 < n_r;){  //till r[j2].Min < l[i].Min
            if (R[j2].Min >= L[i].Min){ //exclude the r_min
                if (j2 < j1){
                    --mod[(p[m+1+j2] - (ll)R[j2].Min)%K];
                }
                ++j2;
            }
            else
                break;
        }
        cnt += mod[rmd_trgt];
    }
    for (i = n_l, j1 = 0, j2 = 0; i > 0; --i){
        rmd_trgt = (p[l+i-1-1] + (ll)L[i].Max)%K;
        /*	maintain the window	*/
        for (; j1 < n_r;){
            if (R[j1].Max <= L[i].Max){
                if (j2 <= j1){
                    --mod[(p[m+1+j1] - (ll)R[j1].Min)%K];
                }
                ++j1;
            }
            else
                break;
        }
        for (; j2 < n_r;){  //till r[j2].Min < l[i].Min
            if (R[j2].Min >= L[i].Min){
                if (j2 < j1){
                    ++mod[(p[m+1+j2] - (ll)R[j2].Min)%K];
                }
                ++j2;
            }
            else
                break;
        }
    }
   
    /*	#4 : max in right, min right	*/
    for (j = 0, i = n_l; j < n_r; ++j){
        rmd_trgt = Mod(p[m+1+j] - R[j].Max - R[j].Min, K);
        for (; i > 0; ){
            if (R[j].Min < L[i].Min && R[j].Max > L[i].Max){
                rmd = (p[l+i-2])%K;
                ++mod[rmd];
                --i;
            }
            else
                break;
        }
        cnt += mod[rmd_trgt]; 
    }
    for (j = 0, i = n_l; j < n_r; ++j){
        rmd_trgt = Mod(p[m+1+j] - R[j].Max - R[j].Min, K);
        for (; i > 0; ){
            if (R[j].Min < L[i].Min && R[j].Max > L[i].Max){
                rmd = (p[l+i-2])%K;
                --mod[rmd];
                --i;
            }
            else
                break;
        }
    }

    return cnt;
}

ll GoodPair(int *a, ll *p, int N, ll *mod, int K, int l, int r){
    ll cnt;
    int i, j;
    int m = (l + r)>>1;
    int n = r - l + 1;
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;   //good pair
    cnt = GoodPair(a, p, N, mod, K, l, m);
    cnt += GoodPair(a, p, N, mod, K, m+1, r);
    cnt += Cross(a, p, N, mod, K, l, m, r);
    return cnt; 

}


int main(int argc, char *argv[])
{
    int i;
    int N, K;
    int *a;
    ll num_of_good_pair;
    ll *p, *mod;
    scanf("%d", &N);
    scanf("%d", &K);

    a   = (int*)malloc((N+1)*sizeof(int));
    p   = (ll*)malloc((N+1)*sizeof(ll));
    mod = (ll*)malloc(K*sizeof(ll));
    
    a[0] = 0;
    for (i = 1; i <= N; i++){
        scanf("%d", &a[i]);
    }
    
    /*	O(N+K)	*/ 
    prefixSum(a, p, N);
    memset(mod, 0, K*sizeof(mod));
    /*	O(NlogN)	*/
    num_of_good_pair = GoodPair(a, p, N, mod, K, 1, N);
    printf("%lld\n", num_of_good_pair); 
    return 0;
}
