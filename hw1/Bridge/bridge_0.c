#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*	The objective function
 *	- (x- x')^2 - (y - y')^2	*/
#define COR_MAX 1000000000 

typedef long long ll;


ll max_net_rev(int *X, int *Y, int N, int *pair){
    int i, j;
    int x_diff = COR_MAX;
    int X_diff;
    int y_diff = COR_MAX;
    int Y_diff;
    ll obj = - (ll) x_diff*x_diff - (ll) y_diff*y_diff;
    ll Obj;    //objective function
    for (i = 0; i < N; i++){
        for (j = i+1; j < N; j++){
            X_diff = X[i] - X[j];
            Y_diff = Y[i] - Y[j];
            Obj = - (ll) X_diff*X_diff - (ll) Y_diff*Y_diff;
            if (Obj >= obj){ 
                pair[0] = i;
                pair[1] = j;
                obj = Obj;            
            }
        }
    } 
    return obj;
}

int main(int argc, char *argv[]){
    int i, N;
    scanf("%d", &N);
    /*	input N 2D-coordinate cities	*/
    int *X = (int*)malloc(N*sizeof(int));
    int *Y = (int*)malloc(N*sizeof(int));
    ll ans;
    for (i = 0; i < N; i++){
        scanf("%d", &X[i]);
        scanf("%d", &Y[i]);
    }
    int pair[2] = {0, 0};
    
    ans = max_net_rev(X, Y, N, pair);
    printf("%lld\n", ans); 
    //printf("Choose ");
    //for (i = 0; i < 2; i++)
    //    printf("%d-th ", pair[i]);
    //printf("\n");
    return 0;
}

