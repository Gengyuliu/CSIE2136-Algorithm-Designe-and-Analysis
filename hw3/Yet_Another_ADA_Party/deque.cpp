#include <stdio.h>
#include <stdlib.h>
#include <deque>
using namespace std;
#define ll long long 

int main(int argc, char *argv[])
{
    int N;
    scanf("%d",&N);
    deque<ll> d;
    for (int i = 0; i < N; ++i){
        d.push_front(i);
    }
    for (auto i : d){
        printf("%lld\n", i);
    }
    
    return 0;
}
