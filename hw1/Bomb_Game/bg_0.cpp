#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <cassert>
#include <vector>
using namespace std;


typedef long long ll;

typedef struct Player{
    ll  k_t;//total kill
    int t;  //time 0 ~ M-1
    int c;  //cell
    int d;  //defense level
} Player;

typedef struct Attack{
    int l;  //attack range within [l, r]
    int r;  
    int p;  //explosive power
    int k;  //demage kill
    int t;  //time 0 ~ M-1
} Attack;


typedef struct Timeline{
    char    Event;
    Player  P;
    Attack  A;
}Timeline;


void Calc_kills(Timeline *T, int M, vector<Timeline> *plys){
    int i, j;
    int c;
    int d, p;
    ll k_t; 
    for (i = 0; i < M; i++){
        if(T[i].Event == 'A')
            continue;
        //P_i
        T[i].P.k_t = 0;
        c = T[i].P.c;
        d = T[i].P.d;
        for(j = i+1; j < M; j++){
            if (T[j].Event == 'P')
               continue;
            
            if (c >= T[j].A.l && c <= T[j].A.r && d <= T[j].A.p){
               T[i].P.k_t += T[j].A.k; 
            } 
             
        }
        plys->push_back(T[i]);       
    }
    return;
}


void printAns(vector<Timeline> &plys){
    int n = plys.size();
    int i;
    for (i = 0; i < n; i++){
        printf("%lld\n", plys[i].P.k_t);
    }
}

int main(int argc, char *argv[])
{
    int N, M;
    int i;      //event index
    char e;

    scanf("%d", &N);
    scanf("%d", &M);
    Timeline *T = (Timeline*)malloc(M*sizeof(Timeline));  
    //ll  *plys   = (ll*)malloc(N*sizeof(plys)); 
    vector<Timeline> plys;        
     
    for (i = 0; i < M; i++){
        getchar();
        T[i].Event = getchar();
        switch(T[i].Event){
            case 'P':
                scanf("%d", &T[i].P.c);
                scanf("%d", &T[i].P.d);
                break;
            case 'A':
                scanf("%d", &T[i].A.l);
                scanf("%d", &T[i].A.r);
                scanf("%d", &T[i].A.p);
                scanf("%d", &T[i].A.k);
                break;
        }
        fflush(stdin);
    } 
    
    Calc_kills(T, M, &plys);  
    printAns(plys);    

    return 0;
}
