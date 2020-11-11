#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>

/*	Discuss with 劉安浚	*/
using namespace std;
typedef long long ll;
typedef struct Segment{
    int idx;
    int L;
    int R;  /*	the range of each segment	*/
    ll  W;  /*	# of segments	*/
}Segment;
namespace Memory {
    constexpr int N = 200010; // Number of cells, change this if you need more cells
    ll arr[N + 1]; // Note: This is NOT the memory itself, please don't try to access this array directly unless you know what you're doing

    /* Start of internal functions */
    void _ins(int x, ll k) {
        while (x <= N)
            arr[x] += k, x += x & -x;
    }

    long long _qr(int x) {
        long long ret = 0;
        while (x) ret += arr[x], x -= x & -x;
        return ret;
    }
    /* End of internal functions */
    
    // Explicitly fill the whole memory with zero
    // Complexity: O(N)
    void reset() {
        for (int i = N; i >= 0; --i)
            arr[i] = 0;
    }

    // Add k to every cell in range [l, r]
    // Complexity: O(log(N))
    void add(int l, int r, ll k) {
        assert(1 <= l && l <= r && r <= N && "add: the argument should satisfy 1 <= l <= r <= N");
        _ins(l, k);
        _ins(r + 1, -k);
    }

    /* Get the value in cell x       Complexity: O(log(N)) */
    ll get(int x) {
        assert(1 <= x && x <= N && "get: x should be a positive integer in range [1, N]");
        return _qr(x);
    }
}

/*	Need to sort according to L_i	*/
bool cmp_L(Segment a, Segment b){
    return a.L < b.L;
}
/*	used for max heap	*/
bool cmp_R(Segment a, Segment b){
    return a.R < b.R;
}

/*	KEY STEP : check if we could fill certain V line segments over [0,M]	*/
/*	0 : fail  1 : success -1 : error*/
int check(Segment *S, int pick, ll *chose_seg, ll V,  int N, int M, ll K){
    /*	Two pointers	*/
    int i;              /*	segments index 0 ~ N-1	*/
    int x;              /*	range [0,M]	*/
    ll v, k;
    vector<Segment> H;  /*	max heap	*/
    if (pick == 1)
        memset(chose_seg, 0, N*sizeof(ll));

    if (V == 0)
        return 1;
     
    /*	Start from f(x=0) = V	*/
    for (i = 0, x = 0; i < N && S[i].L <= x; ++i){
        H.push_back(S[i]);
    }
    /*	i is now at the S[i] s.t. S[i] > x=0	*/
    make_heap(H.begin(), H.end(), cmp_R);
    Memory::reset();

    for (k = 0; x <= M; ){
        /*	          V	         x          <V        M   */  
        /*	|-------------------<|--------------------|	*/
        /*	find the next x+1 s.t. 	*/      
        v = Memory::get(x+1);
        /*	pop out until f(x) = V 	*/
        /*	this tyies to make current x having V covers	*/
        for (;v != V && !H.empty();){
            Segment s = H.front();
            if (x < s.L || x >= s.R){
                pop_heap(H.begin(), H.end(), cmp_R);
                H.pop_back();
                continue;
            }
            
            /* maintain how many W are available	*/
            if ((V - v) >= s.W){    /*	use all W of s	*/ 
                Memory::add(s.L+1, s.R, s.W);
                k += s.W;
                /*	pick here	*/
                if (pick == 1)
                    chose_seg[s.idx] += s.W;
                pop_heap(H.begin(), H.end(), cmp_R);
                H.pop_back(); 
            }
            else{                   /*	use partial W of s	*/
                Memory::add(s.L+1, s.R, V-v);
                k += V - v;
                /*	pick here	*/ 
                if (pick == 1)
                    chose_seg[s.idx] += V-v;
                H.front().W -= V - v;
                if (H.front().W == 0){
                    pop_heap(H.begin(), H.end(), cmp_R);
                    H.pop_back(); 
                } 
            }
            v = Memory::get(x+1);
        } 
        //Here : v == V or H is empty()
        if (v < V)
            return 0;       /*	cannot reach V at x	*/  
        if (k > K)
            return 0;       /*	over the bound K	*/

        /*	take up the range with f(x) >= V 	*/
        for (;Memory::get(x+1) >= V;)
           ++x; 
        
        /*	f(x) < V	*/
        if (x == M)
            return 1;        
        else if (i == N && H.empty()) 
            return 0;       /*  used up all segs, but not reach end */
        
        /*	push those segments with L_i <= x	*/
        for (; i < N && S[i].L <= x; ++i){
            H.push_back(S[i]);
            push_heap(H.begin(), H.end(), cmp_R);
        }
    }
    /*	should not be here	*/
    return -1;
}

/*	S : sorted according to L	*/
void max_range_cover(Segment *S, int N, int M, ll K){
    int i, pick;
    ll V;
    ll l, r, mid;
    ll *chose_seg;
    
    chose_seg = (ll*)malloc(N*sizeof(ll));
    /*	Binary Search	*/
    pick = 0;
    if (check(S, pick, chose_seg, K, N, M, K)){
        pick = 1;
        check(S, pick , chose_seg, K, N, M, K);
        printf("%lld\n", K);
        for (i = 0; i < N; ++i){
            printf("%lld ", chose_seg[i]);
        }
        return;
    }
    //Not handle V = K
    for (pick = 0, l = 0, r = K; l+1 < r;){   /*	logK	*/
        V = (l + r)>>1;
        /*	if m is valid --> l = m+1	*/
        if (check(S, pick, chose_seg, V, N, M, K))
            l = V;      /*	l : valid	*/
        else
            r = V;      /*	r : invalid	*/
    }
    /*	the ans is l	*/ 
    pick = 1;
    check(S, pick, chose_seg, l, N, M, K);
    printf("%lld\n", l);
    for (i = 0; i < N; ++i){
        printf("%lld ", chose_seg[i]);
    } 
    printf("\n"); 
    return; 
}

int main(int argc, char *argv[]){
    int i;
    int N, M;
    ll  K;
    ll  V;
    scanf("%d %d %lld", &N, &M, &K);
    Segment *sets = (Segment*)malloc(N*sizeof(Segment));
    for (i = 0; i < N; ++i){
        sets[i].idx = i;
        scanf("%d %d %lld", &sets[i].L, &sets[i].R, &sets[i].W);
    }
    /*	O(N logN)	*/
    sort(sets, sets+N, cmp_L); 
    /*	O(N logN logK)	*/ 
    max_range_cover(sets, N, M, K); 
    return 0;
}
