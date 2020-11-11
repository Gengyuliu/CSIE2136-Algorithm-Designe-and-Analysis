#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
#include <vector>
using namespace std;

typedef struct Element{
    int pos;
    int a;  //values
    int c;  //cost
    int s;  //score
}Element;

/*	dstn is the reverse of trgt in sequence a	*/
void reverse_seq(Element *dstn, Element *trgt, int N){
    int i;
    for (i = 1; i < N+1; ++i){
        dstn[i] = trgt[N-i+1]; 
    }
    return; 
}


/*	return number of elements	*/
void LCS(Element *X, int n, Element *Y, int m, int *S){
    int i, j;
    int idx;
    int idx_dgnl;
    int idx_up;
    int idx_lft;
    int a, b, c;
    for (i = 0; i < n+1; ++i){
        for (j = 0; j < m+1; ++j){
            idx = i*(m+1) + j;
            if (i == 0 || j == 0){
                S[idx] = 0;
                continue;
            } 
            
            a = S[(i-1)*(m+1) + j];
            b = S[i*(m+1) + j-1];
            c = S[(i-1)*(m+1) + j-1] + X[i].s + Y[j].s;

            if (X[i].a == Y[j].a){
                S[idx] = (c>=a)?(c>=b? c:b):(a>b? a:b); 
            }
            else{
                S[idx] = (a>b)?a:b;
            }
        }
    } 

    printf("LCS table\n     "); 
    for (i = 0; i < m+1; ++i){
        printf("%3d ", Y[i].a);
    }
    printf("\n");
    for (i = 0; i < n+1; ++i){
        printf("%3d |", X[i].a);
        for (j = 0; j < m+1; ++j){
            idx = i*(m+1) +j;
            printf("%3d ", S[idx]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void Back_trace(vector<int> &indices, Element *X, int n, Element *Y, int m,  int *S){
    int i, j;
    int i_max, j_max;
    int a, b, c;
    int Max; 
    for (i = n, j = m; i > 0 && j > 0; ){
        a = S[(i-1)*(m+1)+j];
        b = S[i*(m+1) + j-1];
        c = S[(i-1)*(m+1) + j-1] + X[i].s + Y[j].s;
        
        if (X[i].a == Y[j].a){
            if (c >= b && c >= a){
                indices.push_back(i);
                --i, --j;
            }
            else if (a > c && a > b){
                --i;
            }
            else{
                --j;
            }
        }
        else{
            if (a > b)
                --i;
            else 
                --j;
        }
    }

    return;
}

void print_ans(Element *Seq, int N, vector<int> &indices, int *S){
    int i;
    int X; 
    int M; 
    X = 0;
    
    printf("%d\n", S[N*(N+1)+N]/2);
    printf("%d\n", X);
    M = indices.size();
    
    printf("%d\n", M);
    for (i = M-1; i >= 0 ; --i){
        printf("%d ", indices[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    int N, K, D;
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &D);
    Element *Seq    = (Element*)malloc((N+1)*sizeof(Element));
    Element *rv_Seq = (Element*)malloc((N+1)*sizeof(Element));
    int     *S      = (int*)malloc((N+1)*(N+1)*sizeof(int));
    vector<int> indices;
    
    for (i = 1; i < N+1; ++i){
        Seq[i].pos = i;
        scanf("%d", &Seq[i].a);
    }
    for (i = 1; i < N+1; ++i){
        scanf("%d", &Seq[i].c);
    }
    for (i = 1; i < N+1; ++i){
        scanf("%d", &Seq[i].s);
    }
    /*	LPS	*/ 
    reverse_seq(rv_Seq, Seq, N);
    LCS(Seq, N, rv_Seq, N, S);
    Back_trace(indices, Seq, N, rv_Seq, N, S); 
    
    print_ans(Seq, N, indices, S);
    free(Seq), free(rv_Seq), free(S);
    return 0;
}
