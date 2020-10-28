#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cstring>
#include <stack>
#include <iostream>

using namespace std;

typedef long long ll;

typedef struct Grid{
    ll val;
    int pos[2] = {0, 0};
    int cnt = 0;    //count how many moves
    int mv;     //1: regular move 2: jump
    struct Grid *pre = NULL;
} Grid;

/*	path sum at a grid	*/
typedef struct G_sum{
    ll sum;
    int pos[2];
} G_sum;

/*	only move right or down	*/
/*	0 jump	*/
/*	grids : kmn
 *	f_max : k	*/
void Fill_f0(Grid *grids, ll *f, G_sum *f_max, int n, int m){
    int i, j;
    int idx;
    ll x, y;
    
    //Base case
    f[0] = grids[0].val;
    f_max[0] = {.sum = f[0], .pos = {0, 0}};
    
    //Top col
    for (i = 1; i < n; i++){
        idx = i*m;
        f[idx] = f[idx - m] + grids[idx].val;
        
        grids[idx].pre = &grids[idx - m];
        grids[idx].cnt = grids[idx].pre->cnt + 1;

        if (f[idx] > f_max[0].sum){
            f_max[0].pos[0] = i, f_max[0].pos[1] = 0;
            f_max[0].sum = f[idx];
        }
    }
    //Top row
    for (j = 1; j < m; j++){
        idx = j;
        f[idx] = f[idx - 1] + grids[idx].val;
   
        grids[idx].pre = &grids[idx - 1];
        grids[idx].cnt = grids[idx].pre->cnt + 1;

        if (f[idx] > f_max[0].sum){
            f_max[0].pos[0] = 0, f_max[0].pos[1] = j;
            f_max[0].sum = f[idx];
        }
    }
    //Other grids
    for (i = 1; i < n; i++){
        for (j = 1; j < m; j++){
            idx = i*m + j;
            x = f[idx - m];
            y = f[idx - 1];
            if (x > y){     //move from top
                f[idx] = x + grids[idx].val;

                grids[idx].pre = &grids[idx - m];
            } 
            else{           //move from left
                f[idx] = y + grids[idx].val;

                grids[idx].pre = &grids[idx - 1];
            }

            grids[idx].cnt = grids[idx].pre->cnt + 1;
            
            if (f[idx] > f_max[0].sum){
                f_max[0].pos[0] = i, f_max[0].pos[1] = j;
                f_max[0].sum = f[idx];
            }

        }
    }
    return;
}

/*	grids : Kmn 
 *	f     : Kmn
 *	f_max : K	*/
void Fill_f_table(Grid *grids, ll *f, G_sum *f_max, int n, int m, int K, int c){
    if (K == 1)
        return;
    int i, j, r;
    int idx;
    int idx_jp;
    ll ans; 
    ll a_ij;
    ll x, y, z; 
    
    //memset(f, 0, n*m*K);

    /* O(kmn)		*/
    for (r = 1; r < K; r++){
        /*	for each r-th jump	*/
        idx_jp = (r-1)*n*m + f_max[r-1].pos[0]*m + f_max[r-1].pos[1];
        
        //(i,j) = (0,0)
        idx = r*n*m;
        a_ij = grids[0].val - (ll)r*c;
        f[idx] = f_max[r - 1].sum + a_ij;
        
        grids[idx].pre = &grids[idx_jp];
        grids[idx].cnt = grids[idx].pre->cnt + 1;
        grids[idx].mv  = 2;
      
        f_max[r].sum = f[idx]; 
        f_max[r].pos[0] = 0, f_max[r].pos[1] = 0;
         
        //(i,j) = (0,j) or (i,0)
        for (i = 1; i < n; i++){
            idx = r*n*m + i*m;
            a_ij= grids[i*m].val - (ll)r*c;
            x = f[idx - m];
            y = f_max[r - 1].sum;
            if (x > y){ //move from top
                f[idx] = x + a_ij;
                grids[idx].pre = &grids[idx - m];
            }
            else{       //jump from 
                f[idx] = y + a_ij;
                grids[idx].pre = &grids[idx_jp];
                grids[idx].mv = 2;
            }
            grids[idx].cnt = grids[idx].pre->cnt + 1;

            if (f[idx] > f_max[r].sum){
                f_max[r].sum = f[idx];
                f_max[r].pos[0] = i, f_max[r].pos[1] = 0;
            }
        }
        for (j = 1; j < m; j++){
            idx = r*n*m + j;
            a_ij = grids[j].val - (ll)r*c;
            x = f[idx - 1];
            y = f_max[r - 1].sum;
            if (x > y){ //move from left
                f[idx] = x + a_ij;
                grids[idx].pre = &grids[idx - 1];
            }
            else{       //jump from 
                f[idx] = y + a_ij;
                grids[idx].pre = &grids[idx_jp];
                grids[idx].mv = 2;
            }
            grids[idx].cnt = grids[idx].pre->cnt + 1;
             
            if (f[idx] > f_max[r].sum){
                f_max[r].sum = f[idx];
                f_max[r].pos[0] = 0, f_max[r].pos[1] = j;
            }
        }

        for (i = 1; i < n; i++){
            for (j = 1; j < m; j++){
                idx = r*n*m + i*m + j;
                a_ij = grids[i*m+j].val - (ll)r*c;
                x = f[idx - m] + a_ij;
                y = f[idx - 1] + a_ij;
                z = f_max[r - 1].sum + a_ij;
                if ( x > y && x > z ){      //move from Top
                    f[idx] = x; 
                    grids[idx].pre = &grids[idx - m]; 
                }
                else if ( y > x && y > z ){ //move from left
                    f[idx] = y;
                    grids[idx].pre = &grids[idx - 1];
                }
                else{                       //jump from 
                    f[idx] = z;
                    grids[idx].pre = &grids[idx_jp];
                    grids[idx].mv = 2;
                }            
                grids[idx].cnt = grids[idx].pre->cnt + 1;
                
                if (f[idx] > f_max[r].sum){
                    f_max[r].sum = f[idx];
                    f_max[r].pos[0] = i, f_max[r].pos[1] = j;
                }
 
            }
        }
    }
    return;
}

ll Sum_max(ll *f, int n, int m, int K, int *r_max){
    int r;
    int idx;
    ll sum_max = (ll)-1<<62;
    /*	O(k)	*/ 
    for (r = 0; r < K; r++){
        idx = r*n*m + n*m - 1;
        if (f[idx] > sum_max){
            sum_max = f[idx];
            *r_max = r; 
        }
    }
    //printf("r_max = %d\n", *r_max);
    return sum_max; 
}

void printPath( Grid *grids, int n, int m, int r_max){
    int i, num_path;
    int idx_end;
    int x, y;
    stack<Grid> path;
    Grid cur;

    idx_end = r_max*n*m + n*m - 1;
    cur = grids[idx_end];
    num_path = cur.cnt;
    
    for (i = 0; i < num_path; i++){
        path.push(cur);
        cur = *cur.pre; 
    }    
    printf("%d\n", num_path);
    for (i = 0; i < num_path; i++){
        x = path.top().pos[0];
        y = path.top().pos[1];
        switch(path.top().mv){
            case 1: printf("%s %d %d\n", "Move", x, y);
                    break;
            case 2: printf("%s %d %d\n", "Jump", x, y);
                    break;
        }
        path.pop();
    }
    return;
}

int main(int argc, char *argv[]){
    int i, j, r;
    int n, m, k, c;
    int r_max;
    int idx1, idx2; 
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &c); 
    int K = k + 1;

    Grid    *nuts   = (Grid*)malloc(K*n*m*sizeof(Grid)); 
    G_sum   *f_max  = (G_sum*)malloc(K*sizeof(G_sum));
    ll      *f_table= (ll*)malloc(K*n*m*sizeof(ll));
    //ll      *f_max      = (ll*)malloc(K*sizeof(ll));
    ll ans;

    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            idx1 = i*m + j;
            scanf("%lld", &nuts[idx1].val);
            nuts[idx1].pos[0] = i;
            nuts[idx1].pos[1] = j;         
            //nuts[idx1].cnt = 0;
            nuts[idx1].mv = 1;
            for (r = 1; r < K; r++){
                idx2 = r*n*m + i*m + j;
                nuts[idx2] = nuts[idx1];
            }
        }
    }

    Fill_f0(nuts, f_table, f_max, n, m);
    Fill_f_table(nuts, f_table, f_max, n, m, K, c);
    ans = Sum_max(f_table, n, m, K, &r_max);
    
    printf("%lld\n", ans);
    printPath(nuts, n, m, r_max);
    
    free(nuts);
    free(f_max);
    free(f_table);
    return 0;
}
