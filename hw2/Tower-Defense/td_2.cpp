#include <stdio.h>
#include <stdlib.h>
#include <cstring>
/*	Goal : maximize the total defense level	*/
/*	To save space : keep the most recent two rows	*/
#define LAST(x, n) ((x) & ((1<<(n)) - 1))   //extract the last n bit of x

typedef long long ll;

typedef struct Cell{
    ll val;
    int idx;
}Cell;
/*	S_(i,t) : a tower built at cell i and there are t towers already built till cell i	*/
ll Fill_table(ll *S, ll *s, int N, int K, int A, int B){
    int t, i, j;
    ll nearest; 
    ll max_df;
    Cell Max;
    Cell *prefix_max = (Cell*)malloc((N+1)*sizeof(Cell));
    int now, pre;
    int idx_now, idx_pre;

    max_df = 0;
    for (t = 1; t <= K; ++t){
        now = LAST(t, 1);
        pre = now ^ 1;
        if (t == 1){
            for (i = 1; i <= N; ++i){
                idx_now = now*(N+1)+i;
                S[idx_now] = s[i];
                max_df = (S[idx_now]>max_df)?S[idx_now]:max_df;
            }
        }
        else{
            prefix_max[0].val = -(ll)1<<60;
            prefix_max[0].idx = 0;
            for (i = 1; i <= N; ++i){
                idx_pre = pre*(N+1) + i;
                if (S[idx_pre] > prefix_max[i-1].val){
                    prefix_max[i].val = S[idx_pre];
                    prefix_max[i].idx = i;
                }
                else{
                    prefix_max[i].val = prefix_max[i-1].val;
                    prefix_max[i].idx = prefix_max[i-1].idx;
                }            
            }
             
            for (i = 1; i <= N; ++i){
                idx_now = now*(N+1) + i;
                idx_pre = pre*(N+1) + i;
                if (t > i){
                    S[idx_now] = 0;
                    continue;
                }
                S[idx_now] = s[i]; 
                nearest = S[idx_pre - 1] + (ll)A*(B-1);
                j = (i-B > 0)?(i-B):0; 
                 
                
                if (i == t){
                    Max.val = nearest;
                    Max.idx = i-1;
                }
                else{
                    if (nearest > Max.val && nearest > prefix_max[j].val){
                        Max.val = nearest;
                        Max.idx = i-1;
                    }
                    else if (prefix_max[j].val>Max.val && prefix_max[j].val>=nearest){
                        Max.val = prefix_max[j].val;
                        Max.idx = prefix_max[j].idx;
                    }
                }

                S[idx_now] += Max.val;
                max_df = (S[idx_now]>max_df)?S[idx_now]:max_df;
                /*	consider the next one	*/
                if (Max.idx - 1 > j){
                    Max.val -= (ll)A;
                }
                else{
                    Max.val = S[pre*(N+1)+Max.idx];
                }
            }
        }
    }

//    for (t = 0; t <= K; ++t){
//        for (i = 0; i <= N; ++i){
//            printf("%3lld ", S[t*(N+1)+i]);
//        }
//        printf("\n");
//    }
    free(prefix_max);
    return max_df;
}



int main(int argc, char *argv[])
{
    int i;
    int N, K, A, B;
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &A);
    scanf("%d", &B);
    ll *s       = (ll*)malloc((N+1)*sizeof(ll));
    ll *S       = (ll*)malloc(2*(N+1)*sizeof(ll));
    ll max_df;

    s[0] = 0;
    for (i = 1; i <= N; ++i){
        scanf("%lld", &s[i]);
    }
    
    memset(S, 0, 2*(N+1)*sizeof(S));        
    max_df = Fill_table(S, s, N, K, A, B);
    printf("%lld\n", max_df);
    free(s), free(S);
    return 0;
}
