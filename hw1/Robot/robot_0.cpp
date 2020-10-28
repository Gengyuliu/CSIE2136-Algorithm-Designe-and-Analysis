#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
#include <stack>
using namespace std;

typedef long long ll;

typedef struct Grid{
    int pos[2] = {0, 0};
    ll val;
    int count = 0;
    struct Grid *pre = NULL;
} Grid;


ll Max_sum(Grid *grids, ll *memo, int n, int m){
    int i, j;
    ll ans; 
    //Base case 
    memset(memo, 0, n*m);
    memo[0] = grids[0].val;
    //Top row
    for (i = 1; i < n; i++){
        memo[i*m] = memo[(i-1)*m] + grids[i*m].val;
        grids[i*m].pre = &grids[(i-1)*m];
        grids[i*m].count = grids[i*m].pre->count + 1; 
    }
    //Top col
    for (j = 1; j < m; j++){
        memo[j] = memo[j - 1] + grids[j].val;
        grids[j].pre = &grids[j - 1];
        grids[j].count = grids[j].pre->count + 1;
    }

    for (i = 1; i < n; i++){
        for (j = 1; j < m; j++){
            if (memo[(i-1)*m + j] > memo[i*m + (j-1)]){
                memo[i*m + j] = memo[(i-1)*m + j] + grids[i*m + j].val;
                grids[i*m + j].pre = &grids[(i-1)*m + j];
            }
            else{
                memo[i*m + j] = memo[i*m + (j-1)] + grids[i*m + j].val;
                grids[i*m + j].pre = &grids[i*m + (j-1)];
            }
            grids[i*m + j].count = grids[i*m + j].pre->count + 1;
        }
    }
     
    return memo[(n-1)*m + m-1];
}

void PrintAns(Grid *grids, int n, int m){
    int i;
    int x, y;
    int num = grids[n*m - 1].count;
    stack<Grid> path;
    Grid cur = grids[n*m - 1];
    Grid pre;
    
    for (i = 0; i < num; i++){
        path.push(cur);
        pre = *cur.pre; 
        cur = pre; 
    }

    printf("%d\n", num);
    for (i = 0; i < num; i++){
        x = path.top().pos[0];
        y = path.top().pos[1];
        printf("%s %d %d\n", "Move", x, y);
        path.pop();
    }

    return;
}


int main(int argc, char *argv[]){
    int i, j;
    int n, m, k, c;
    
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &c);
    
    Grid *nuts    = (Grid*)malloc(n*m*sizeof(Grid)); 
    ll *max_sum = (ll*)malloc(n*m*sizeof(ll));
    ll ans;
     
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            scanf("%lld", &nuts[i*m + j].val);
            nuts[i*m + j].pos[0] = i;
            nuts[i*m + j].pos[1] = j;         
        }
    }
    
    ans = Max_sum(nuts, max_sum, n, m);
    
    printf("%lld\n", ans);
    PrintAns(nuts, n, m);
    return 0;
}
