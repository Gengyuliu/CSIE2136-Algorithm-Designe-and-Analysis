#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
typedef struct Element{
    int pos;
    int a;  //values
    int c;  //cost
    int s;  //score
}Element;

/*	dstn is the reverse of trgt in sequence a	*/
void reverse_seq(Element *dstn, Element *trgt, int N){
    int i;
    memset(dstn, 0, (N+1)*sizeof(dstn)); 
    for (i = 1; i < N+1; ++i){
        dstn[i] = trgt[N-i+1]; 
    }
    return; 
}



int LCS(Element *X, int n, Element *Y, int m, int *L){
    int i, j;
    int idx;
    int idx_dgnl;
    int idx_up;
    int idx_lft;
    for (i = 0; i < n+1; ++i){
        for (j = 0; j < m+1; ++j){
            idx         = i*(m+1) + j; 
            idx_dgnl    = idx - (m+1) - 1;
            idx_up      = idx - (m+1);
            idx_lft     = idx - 1;
            
            if (i == 0 || j == 0){
                L[idx] = 0;
            } 
            else if (X[i].a == Y[j].a){
                L[idx] = L[idx_dgnl] + 1; 
            }
            else{
                L[idx] = (L[idx_up]>L[idx_lft])?L[idx_up]:L[idx_lft];
            }
        }
    } 

//    printf("LCS table\n   "); 
//    for (i = 0; i < m+1; ++i){
//        printf("%d ", Y[i].a);
//    }
//    printf("\n");
//    for (i = 0; i < n+1; ++i){
//        printf("%d |", X[i].a);
//        for (j = 0; j < m+1; ++j){
//            idx = i*(m+1) +j;
//            printf("%d ", L[idx]);
//        }
//        printf("\n");
//    }

    return L[n*(m+1)+m];
}

void Back_trace(int *indices, int M, Element *X, int n, Element *Y, int m,  int *L){
    int i, j, k;
    for (i = n, j = m, k = M; i > 0 && j > 0 && k > 0;){
        if (X[i].a == Y[j].a){
            indices[k] = i;
            --i, --j, --k; 
        } 
        else if (L[(i-1)*(m+1)+j] > L[i*(m+1)+j-1])
            --i;
        else
            --j;
    }
    return;
}

void print_ans(Element *Seq, int N, int *indices, int M){
    int i;
    int S;
    int X; 
    
    S = 0;
    for (i = 1; i < M+1; ++i){
        S += Seq[indices[i]].s;
    }
    X = 0;

    printf("%d\n", S);
    printf("%d\n", X);
    printf("%d\n", M);
    for (i = 1; i < M+1; ++i){
        printf("%d ", indices[i]); 
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i;
    int N, K, D;
    int M;
    scanf("%d", &N);
    scanf("%d", &K);
    scanf("%d", &D);
    Element *Seq    = (Element*)malloc((N+1)*sizeof(Element));
    Element *rv_Seq = (Element*)malloc((N+1)*sizeof(Element));
    int     *L      = (int*)malloc((N+1)*(N+1)*sizeof(int)); 

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
    //printf("reverse done\n");
    M = LCS(Seq, N, rv_Seq, N, L);
    int *indices = (int*)malloc((M+1)*sizeof(int));
    Back_trace(indices, M, Seq, N, rv_Seq, N, L); 
    
    print_ans(Seq, N, indices, M);
    free(Seq), free(rv_Seq), free(L), free(indices);
    return 0;
}
