#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <vector>
using namespace std;
typedef long long ll;
/*	2 <= n <= 10^5	*/
/*	{c_i | c_i books with thickness i}	*/
void greedy(int *c, int n, int flag){
    int i, j;
    int i_init, i_end, i1;
    int c_top[4] = {0};
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
    if (n == 2){
        c[i_init + 2] = 0;
    }
    for (i = 1; i < 4; ++i){
        c_top[i] = c[i_init + i-1];
    }
    /*	the for loop -> change the array c to makes it beautiful	*/ 
    for (cnt = 0, i = i_init; i <= i_end; ){
        if (c[i] == 0){
            if (i < i_end)
                cnt += (ll)1;
            ++i;
            continue;
        }
        /*	c[i] != 0	*/
        if (i == i_end){
            cnt += (ll)c[i] - (ll)1;
            ++i;
            continue; 
        }
        /*	c[i] != 0 && 0 < i < i_end	*/
        if (i == i_init && c[i+1]-1 >= c[i] + c[i+2]){
            cnt += (ll)c[i_init+1]-(ll)1 - (ll)c[i_init] - (ll)c[i_init+2]; 
            c[i+2] = 0;
            i = i+2;
            continue;
        } 
        
        if (c[i+1] >= c[i]-1){
            c[i+1] -= c[i]-1;
        }
        else{
            cnt += (ll)c[i] - (ll)1 - (ll)c[i+1];
            c[i+1] = 0;    
        }
        ++i;
    }
    
    /*	Get the beautiful sequence with the array c[i]	*/
    for (i = i_init; i <= i_end && flag == 1; ){
        if (c[i] == 0){
            if (i < i_end)
                b_seq.push_back(i);
            ++i;
            continue;
        }
        /*	c[i] != 0	*/
        if (i == i_end){
            for (j = 0, mark = 0; j < 2*c[i]-1; ++j, mark ^= 1){
                if (mark == 0)
                    b_seq.push_back(i);
                else{
                    if (i == 1)
                        b_seq.push_back(i+1);
                    else
                        b_seq.push_back(i-1);
                }
            }  
            ++i;
            continue;
        }

        if (i == i_init && c_top[2] - 1 >= c_top[1] + c_top[3]){
            for (j = 0, mark = 0,i1 = 0; j < 2*c[i+1]-1; ++j, mark ^= 1){
                if (mark == 0)
                    b_seq.push_back(i_init+1);
                else{
                    /*	complete the special case here!!!!!!!	*/
                    if (i1 < c_top[1] || c_top[3] == 0){
                        b_seq.push_back(i_init);
                    }
                    else if (i1 >= c_top[1] && c_top[3] != 0){
                        b_seq.push_back(i_init+2);
                    }
                    ++i1;
                }
            } 
            i = i + 2;
            continue;
        }
        for (j = 0, mark = 0; j < 2*c[i]-1; ++j, mark ^= 1){
                if (mark == 0)
                    b_seq.push_back(i);
                else
                    b_seq.push_back(i+1);
        }
        ++i; 
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
    int *c = (int*)malloc((n+3)*sizeof(int));
    for (i = 1; i < n+1; ++i){
        scanf("%d", &c[i]);
    }
    scanf("%d", &flag);
    greedy(c, n, flag); 
    return 0;
}
