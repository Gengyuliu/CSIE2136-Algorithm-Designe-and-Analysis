#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <vector>
using namespace std;
typedef long long ll;
/*	{c_i | c_i books with thickness i}	*/
void greedy(int *c, int n, int flag){
    int i, j;
    int i_init, i_end, i1;
    ll cnt;
    int mark;
    vector<int> b_seq;
    /*	guarenteed at least one c_i is non-zero	*/ 
    /*	find the first  and the last nonzero c_i	*/
    for (i = 1, i_init = 0; i < n+1; ++i){
        if (c[i] != 0){
            i_init = i;
            break;
        }
    }
    for (i = n, i_end = 0; i > 0; --i){
        if (c[i] != 0){
            i_end = i;
            break;
        }
    }

    /*	the for loop -> change the array c to makes it beautiful	*/ 
    for (cnt = 0, i = i_init; i <= i_end; ++i){
        if (c[i] == 0)
            cnt += (ll)1;
        else{
            cnt += (ll)c[i] - (ll)1;
        } 
        
        
        //if (c[i] == 0){
        //    if (i < i_end)
        //        cnt += 1;
        //    continue;
        //}
        /*	c[i] != 0	*/
        
        
        /*	c[i] != 0 && 0 < i < i_end	*/
        //if (i == i_init && c[i+1]-1 >= c[i] + c[i+2]){
        //    cnt += c[i_init+1]-1 - c[i_init] - c[i_init+2]; 
        //    c[i_init+2] = 0;
        //    i = i+2;
        //    continue;
        //} 
        //
    }
    
    
    printf("%lld\n", cnt);
    if (flag == 1){
        for (i = 0; i < b_seq.size(); ++i)
            printf("%d ", b_seq[i]);
        printf("\n");
    }
    return;
}

int main(int argc, char *argv[]){
    int i;
    int n;
    int flag;
    scanf("%d",&n);
    int *c = (int*)malloc((n+1)*sizeof(int));
    for (i = 1; i < n+1; ++i){
        scanf("%d", &c[i]);
    }
    scanf("%d", &flag);
    greedy(c, n, flag); 
    return 0;
}



