/*	Reference	*/
/*	https://www.geeksforgeeks.org/knapsack-with-large-weights/#:~:text=Given%20a%20knapsack%20with%20capacity,X%20capacity%20of%20the%20knapsack.	*/
/*	https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/	*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
#include <vector>
using namespace std;

#define s_MAX 3
typedef long long ll;
typedef struct Element{
    int pos;
    int a;  //values
    ll c;   //cost
    int s;  //score
}Element;

typedef struct Pair{
    int pos;
    int val;
}Pair;

/*	return number of elements	*/
void DP(int *S, Element *A, ll *C, int N, int K, int D){
    int l;
    int i, j, s;
    int idx;
    int idx1, idx2, idx3, idx4;
    ll u, v, w, x;
    ll c_min;
    ll s_max;
    
    /*	O(s_MAX*N^3)	*/ 
    for (s = 0; s < s_MAX*N+2; ++s){
        for (l = 1; l < N+1; ++l){
            for (i = 1; i < N-l+2; ++i){
                j = i + l - 1;
                idx = s*(N+1)*(N+1) + i*(N+1) + j;
                
                /*	length = 1	*/
                if (l == 1){
                    if (A[i].s >= s)
                        C[idx] = 0;
                    else
                        C[idx] = K+1;
                    continue;
                } 

                /*	length >= 2	*/
                idx1 = s*(N+1)*(N+1) + (i+1)*(N+1) + j;
                idx2 = s*(N+1)*(N+1) + i*(N+1) +j-1;
                u = C[idx1];
                v = C[idx2];
                c_min = (A[i].c < A[j].c)? A[i].c:A[j].c;
                if (A[i].s + A[j].s >= s){
                    if (l == 2){
                        if (abs(A[i].a - A[j].a) <= D)
                            C[idx] = 0;
                        else{
                            s_max = (A[i].s > A[j].s)?A[i].s:A[j].s;
                            if (s_max >= s)
                                C[idx] = 0;
                            else
                                C[idx] = c_min;
                        }
                    }
                    else{
                        if (abs(A[i].a - A[j].a) <= D)
                            C[idx] = 0;
                        else
                            C[idx]=(u < v)?(c_min<=u?c_min:u):(c_min<=v?c_min:v); 
                            //C[idx] = 0;
                    }
                    continue;
                }
                else{
                    if (l == 2){
                        C[idx] = K+1;
                        continue;
                        //printf("i = %d idx4 %lld\n", i, C[idx4]);
                    }
                    else
                        idx3 = (s-A[i].s-A[j].s)*(N+1)*(N+1) + (i+1)*(N+1)+ j-1;
                } 
                     

                if (abs(A[i].a - A[j].a) <= D){
                    w = C[idx3];
                }
                else{
                    w = C[idx3] + c_min;
                }
                C[idx] = (w <= u)?(w <= v? w:v):(u < v? u:v); 
                 
            }
        }
        idx = s*(N+1)*(N+1) + (N+1) + N;//(s,1,N)
        if (C[idx] > K){
            *S = s - 1;
            break; 
        }
    }
    //printf("Table\n "); 
    //for (s = 0; s <= *S+1; ++s){
    //    printf("s = %d\n     ", s);
    //    for (j = 0; j < N+1; ++j){
    //        printf("%4d ", A[j].a);
    //    }
    //    printf("\n");
    //    for (i = 0; i < N+1; ++i){
    //        printf("%3d |", A[i].a);
    //        for (j = 0; j < N+1; ++j){
    //            idx = s*(N+1)*(N+1)+i*(N+1) +j;
    //            printf("%4lld ", C[idx]);
    //        }
    //        printf("\n");
    //    }
    //    printf("\n");
    //}
    //printf("S_max = %d\n", *S);
    return;
}

void Back_trace(int S, Element *A, ll *C, int N, int K, int D){
    int l;
    int s, i, j;
    int idx;
    int idx1, idx2, idx3;
    int c_min;
    int stop;
    int X, M;
    vector<int> ada_seq_idx(N+1, 0); /*	ADA sequence indices	*/
    vector<Pair> change;             /*	index that change val	*/   
   
    stop = 0; 
    for (s = S, i = 1, j = N; stop == 0; ){
        l = j - i + 1;
        if (l == 1){    //j = i
            if (A[i].s >= s){
                /*	end	*/
                ada_seq_idx[i] = A[i].a;
                stop = 1;
                continue;
            }
        }
        
        idx = s*(N+1)*(N+1) + i*(N+1) + j; 
        idx1 = s*(N+1)*(N+1) + (i+1)*(N+1) +j;
        idx2 = s*(N+1)*(N+1) + i*(N+1) + j-1; 
        c_min = (A[i].c < A[j].c)? A[i].c:A[j].c;
        if (A[i].s + A[j].s >= s){
            /*	end	*/
            if (l == 2){ //j = i+1
                if (abs(A[i].a - A[j].a) <= D){
                    ada_seq_idx[i] = A[i].a;
                    ada_seq_idx[j] = A[j].a;
                    s -= A[i].s + A[j].s;
                }
                else{
                    if (A[i].s >= s){
                        ada_seq_idx[i] = A[i].a;
                        s -= A[i].s;
                        --j;
                    }
                    else if ( A[j].s >= s){
                        ada_seq_idx[j] = A[j].a;
                        s -= A[j].s;
                        ++i;
                    }
                    else{
                        ada_seq_idx[i] = A[i].a;
                        ada_seq_idx[j] = A[j].a;
                        s -= A[i].s + A[j].c;
                        // do the modification 
                        Pair p;
                        if (C[idx] == A[i].c){
                            p.pos = i;
                            p.val = A[j].a;
                        }
                        else{
                            p.pos = j;
                            p.val = A[i].a;
                        }
                        change.push_back(p);
                    }
                }
                stop = 1;
                continue;
            }
            else{ /*	l > 2	*/
                if (abs(A[i].a - A[j].a) <= D){
                    ada_seq_idx[i] = A[i].a;
                    ada_seq_idx[j] = A[j].a;
                    s -= A[i].s + A[j].s;
                    ++i, --j;
                    continue;
                }
                else{
                    if (C[idx] == c_min){
                        ada_seq_idx[i] = A[i].a;
                        ada_seq_idx[j] = A[j].a;
                        s -= A[i].s + A[j].s;
                        // do the modification 
                        Pair p;
                        if (C[idx] == A[i].c){
                            p.pos = i;
                            p.val = A[j].a;
                        }
                        else{
                            p.pos = j;
                            p.val = A[i].a;
                        }
                        change.push_back(p);
                        continue;
                    }
                    else if (C[idx] == C[idx1]){
                        ++i;
                        continue;
                    }
                    else if (C[idx] == C[idx2]){
                        --j;
                        continue;
                    }
                }
            } 
        }
        else{
            idx3 = (s-A[i].s-A[j].s)*(N+1)*(N+1) + (i+1)*(N+1) + j-1;
        } 
        /*	s > s_i + s_j	*/
        if (abs(A[i].a - A[j].a) <= D){
            if (C[idx] == C[idx3]){
                ada_seq_idx[i] = A[i].a;
                ada_seq_idx[j] = A[j].a;
                s -= A[i].s + A[j].s; 
                ++i, --j;
            }
            else if(C[idx] == C[idx1])
                ++i;
            else
                --j;
        }
        else{    
            if (C[idx] == C[idx3] + c_min){
                ada_seq_idx[i] = A[i].a;
                ada_seq_idx[j] = A[j].a;
                s -= A[i].s + A[j].s;
                
                Pair p;
                if (c_min == A[i].c){
                    p.pos = i;
                    p.val = A[j].a; 
                }
                else{
                    p.pos = j;
                    p.val = A[i].a;
                }
                change.push_back(p);
                ++i, --j;
            }
            else if(C[idx] == C[idx1])
                ++i;
            else 
                --j;
        }
    }

    X = change.size();
    for (i = 1, M = 0; i < N+1; ++i){
        if (ada_seq_idx[i] != 0)
            ++M;
    }
    
    printf("%d\n", S);
    if (K == 0){
        printf("%d\n", X);
    }
    else{
        printf("%d\n", X);
        for (int x = 0; x < X; ++x){
            printf("%d %d\n", change[x].pos, change[x].val);
        }
    }
    printf("%d\n", M);
    for (i = 1; i < N+1; ++i){
        if (ada_seq_idx[i] != 0)
            printf("%d ", i);
    }
    printf("\n");
    return;
}


int main(int argc, char *argv[])
{
    int i;
    int N, K, D;
    int S;  //max score
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &D);
    Element *Seq    = (Element*)malloc((N+1)*sizeof(Element));
    ll      *C      = (ll*)malloc((s_MAX*N+2)*(N+1)*(N+1)*sizeof(ll));
    
    for (i = 1; i < N+1; ++i){
        Seq[i].pos = i;
        scanf("%d", &Seq[i].a);
    }
    for (i = 1; i < N+1; ++i){
        scanf("%lld", &Seq[i].c);
    }
    for (i = 1; i < N+1; ++i){
        scanf("%d", &Seq[i].s);
    }
    /*	LPS	*/ 
    DP(&S, Seq, C, N, K, D);
    Back_trace(S, Seq, C, N, K, D); 
    
    //print_ans(Seq, N, indices, S);
    free(Seq), free(C);
    return 0;
}
