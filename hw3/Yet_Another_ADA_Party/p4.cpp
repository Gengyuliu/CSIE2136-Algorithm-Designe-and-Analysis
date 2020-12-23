#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <utility>
#include <deque>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define BUFF_SIZE 64
#define Group pair<int,ll>
/*	N types	*/
void solve(){
    int N, Q;
    char s[BUFF_SIZE]; int t; ll c, k;
    deque <Group> party;    
    scanf("%d %d", &N, &Q);
    ll tmp;
    ll *C = (ll*)malloc((N+1)*sizeof(ll));
    
    //mem(ans,0);
    for (int i = 0; i < Q; ++i){
        scanf("%s %lld %d %lld",s,&c,&t,&k);
        Group g = make_pair(t, c+k);
        C[t] += (Q-i)*(c+k); 
        if (strcmp(s, "front") == 0){
            for (;!party.empty() && k >= party.front().second ;){
                k -= tmp;
                C[party.front().first] -= (Q-i)*party.front().second;
                party.pop_front();
            }
            if (k && !party.empty()){
                party.front().second -= k;
                C[party.front().first] -= (Q-i)*k;
                k = 0;
            }
            party.push_front(g);
        }    
        else if (strcmp(s, "back") == 0){
            for (; !party.empty() && k >= party.back().second;){
                k -= tmp;
                C[party.back().first] -= (Q-i)*party.back().second;
                party.pop_back();
            }
            if (k && !party.empty()){
                party.back().second -= k;
                C[party.back().first] -= (Q-i)*k;
            }
            party.push_back(g); 
        }   
    }
    
    for (int i = 1; i < N+1; ++i){
        printf("%lld ", C[i]);
    }
    printf("\n"); 
    return;
}
int main(int argc, char *argv[]){
    solve();
    return 0;
}
