#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
/*	Goal : maximize the total defense level	*/
typedef long long ll;

/*	S_(i,t) : a tower built at cell i and there are t towers already built till cell i	*/
ll Fill_table(ll *S, ll *s, int K, int N, int A, int B){
    int t, i, j;
    ll pre_max, nearest;
    ll max_S;
    ll temp;
    ll S_pre;

    t = 1;
    for (i = 1; i <= N; ++i){
        S[t*(N+1) + i] = s[i];
    }
    for (t = 2; t <= K; ++t){
        for (i = t; i <= N; ++i){
            max_S = -((ll)1<<60);
            for (j = t-1; j < i; ++j){
                temp = (ll)B -(ll)(i - j);
                temp = (temp > 0)? temp:0;
                S_pre = S[(t-1)*(N+1) + j] + (ll)A*temp;  
                max_S = (S_pre > max_S)? S_pre:max_S;
            }
            S[t*(N+1)+i] = s[i] + max_S;
        }
    }

//    for (t = 0; t <= K; ++t){
//        for (i = 0; i <= N; ++i){
//            printf("%3lld ", S[t*(N+1)+i]);
//        }
//        printf("\n");
//    }
    ll Max = 0;
    for (t = 1; t <= K; ++t){
        for (i = t; i <= N; ++i){
            Max = (S[t*(N+1)+i] > Max)? S[t*(N+1)+i]:Max;
        }
    } 
    return Max;
}


int main(int argc, char *argv[])
{
    int i;
    int N, K, A, B;
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &A);
    scanf("%d", &B);
    
    ll *s = (ll*)malloc((N+1)*sizeof(ll));
    ll *S = (ll*)malloc((K+1)*(N+1)*sizeof(ll));
    ll ans;
    s[0] = 0;
    for (i = 1; i <= N; ++i){
        scanf("%lld", &s[i]);
    }
    
    memset(S, 0, (K+1)*(N+1)*sizeof(S));        
    ans = Fill_table(S, s, K, N, A, B);
    printf("%lld\n", ans);
    
    free(s), free(S);
    return 0;
}
