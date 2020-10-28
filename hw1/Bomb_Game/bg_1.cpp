#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <vector>
#include "./helper.h"
using namespace std;

typedef long long ll;

typedef struct Player{
    int idx;    //the idx-th player
    int c;      //cell
    int d;      //defense level
} Player;

typedef struct Attack{
    int l;  //attack range within [l, r]
    int r;  
    int p;  //explosive power
    int k;  //demage kill
} Attack;


typedef struct Event{
    char    e;  //which event
    Player  P;
    Attack  A;
}Event;


void Combine(Event *evnts, int l, int m, int r, vector<ll> &plys_k){
    int i, j, k;
    int n_l = m - l + 1;
    int n_r = r - m;
    int idx;
    char e_l, e_r;
    Event *L = (Event*)malloc(n_l*sizeof(Event));
    Event *R = (Event*)malloc(n_r*sizeof(Event));
   
    vector<int> unset_idx; 
    int *L_dp = (int *)malloc(n_l*sizeof(int));
    int *R_dp = (int *)malloc(n_r*sizeof(int));

    /*	Compute k_t	*/ 
    //while ( i < n_l && j < n_r ){
    for (i=0, j=0; i<n_l && j<n_r; ){
        e_l = evnts[l + i].e;
        e_r = evnts[m + 1 + j].e;
        if (e_l == 'P'){
            if (e_r == 'A'){
                if (evnts[l+i].P.d > evnts[m + 1 + j].A.p){
                    plys_k[evnts[l+i].P.idx] += Memory::get(evnts[l+i].P.c);  //extract k
                    i++;    //deny Attack
                }
                else{
                    Memory::add(evnts[m+1+j].A.l, evnts[m+1+j].A.r, evnts[m+1+j].A.k);
                    unset_idx.push_back(m+1+j);
                    j++;    //accept Attack
                }
            }
            else{
                j++;
            }
        }
        else{   //e_l == 'A'
            if (e_r == 'P')
                i++, j++;
            else
                i++;
        }
    
    }
    
    for (; i < n_l; i++){
        e_l = evnts[l + i].e;
        if (e_l == 'P'){
            plys_k[evnts[l+i].P.idx] += Memory::get(evnts[l+i].P.c);
        }
    }
    
    //unset the k in the range l~r
    for (i = 0; i < unset_idx.size(); i++){
        idx = unset_idx[i];
        Memory::add(evnts[idx].A.l, evnts[idx].A.r, -evnts[idx].A.k);
    } 

    /*	Merge according to their d or p*/
    for (i = 0; i < n_l; i++){
        L[i] = evnts[l + i];
        switch (L[i].e){
            case 'P':   
                L_dp[i] = L[i].P.d;
                break;
            case 'A':
                L_dp[i] = L[i].A.p;
                break;
        }
    }

    for (j = 0; j < n_r; j++){
        R[j] = evnts[m + 1 + j];
        switch (R[j].e){
            case 'P':   
                R_dp[j] = R[j].P.d;
                break;
            case 'A':
                R_dp[j] = R[j].A.p;
                break;
        }

    }
    
    for (i=0, j=0, k=l; i<n_l && j<n_r; k++){
        if (L_dp[i] >= R_dp[j]){
            evnts[k] = L[i];
            i++;
        }
        else{
            evnts[k] = R[j];
            j++;
        }
    }

    for (; i<n_l; k++, i++){
        evnts[k] = L[i];
    }

    for (; j<n_r; k++, j++){
        evnts[k] = R[j];
    }

    free(L), free(R);
    free(L_dp), free(R_dp);
}

void DC(Event *evnts, int l, int r, vector<ll> &plys_k){
    if (l == r)
        return;
    
    int m = (l + r)>>1;
    DC(evnts, l, m, plys_k);
    DC(evnts, m+1, r, plys_k);
    Combine(evnts, l, m, r, plys_k);
    
    return;
}


void printAns(vector<ll> &plys_k){
    int i;
    int n = plys_k.size();
    for (i = 0; i < n; i++){
        printf("%lld\n", plys_k[i]);
    }
}


int main(int argc, char *argv[])
{
    int N, M;
    int i;      //event index
    int idx;
    char e;

    scanf("%d", &N);
    scanf("%d", &M);
    Event *evnts = (Event*)malloc(M*sizeof(Event));
    vector<ll> plys_k;  //order in timeline
   
    idx = 0; 
    for (i = 0; i < M; i++){
        getchar();
        evnts[i].e = getchar();
        switch(evnts[i].e){
            case 'P':
                scanf("%d", &evnts[i].P.c);
                scanf("%d", &evnts[i].P.d);
                evnts[i].P.idx = idx; 
                plys_k.push_back(0);
                idx++;
                break;
            case 'A':
                scanf("%d", &evnts[i].A.l);
                scanf("%d", &evnts[i].A.r);
                scanf("%d", &evnts[i].A.p);
                scanf("%d", &evnts[i].A.k);
                break;
        }
    }

    Memory::reset();
    DC(evnts, 0, M-1, plys_k);  
    printAns(plys_k);    
    
    free(evnts);
    return 0;
}
