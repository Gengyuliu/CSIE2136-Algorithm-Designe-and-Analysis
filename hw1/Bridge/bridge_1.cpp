/*	The Closest-Pair Algorithm	*/
/*	O(NlogN)	*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>
#include <vector>

using namespace std;

#define COR_MAX 1000000000 
#define min(a, b) ((a < b)? a:b)

#define X_coord 0
#define Y_coord 1

typedef long long ll;

/*	2D	*/
typedef struct Point{
    int x;
    int y;
} Point;

void printP(Point *p, int size){
    int i;
    for (i = 0; i < size; i++){
        printf("%d %d\n", p[i].x, p[i].y);
    }
}

ll Euclidean_d2(Point *a, Point *b){
    int x_diff = a->x - b->x;
    int y_diff = a->y - b->y;
    return  (ll)x_diff*x_diff + (ll)y_diff*y_diff;
}


void merge(Point *sorted_pts, int l, int m, int r, int Coordinate, int *repeat_pts){
    int i, j, k;
    int n1 = m - l + 1; //len(left)
    int n2 = r - m;     //len(right)

    Point *L = (Point*)malloc(n1*sizeof(Point));
    Point *R = (Point*)malloc(n2*sizeof(Point));

    for (i = 0; i < n1; i++){
        L[i] = sorted_pts[l + i];
        //printf("%d\n", L[i]);
    }
    for (j = 0; j < n2; j++){
        R[j] = sorted_pts[m + 1 + j];
        //printf("%d\n", R[j]);
    }

    /*	merge left and right	*/
    i = 0, j = 0, k = l;
    if (Coordinate == 0){        
        while( i < n1 && j < n2 ){
            //sort according to x or y(if x are the same)
            if(L[i].x < R[j].x){  
                sorted_pts[k] = L[i];
                i++; 
            }
            else if(L[i].x > R[j].x){
                sorted_pts[k] = R[j];
                j++;
            }
            else{
                if(L[i].y < R[j].y){
                    sorted_pts[k] = L[i];
                    i++;
                }
                else if(L[i].y > R[j].y){
                    sorted_pts[k] = R[j];
                    j++;
                }
                else{
                    *repeat_pts = 1;
                    return;
                }
            }
            k++;
        }
    }
    else{
         while( i < n1 && j < n2 ){
            if (L[i].y <= R[j].y){  //sort according to y-coordinated
                sorted_pts[k] = L[i];
                i++; 
            }
            else{
                sorted_pts[k] = R[j];
                j++;
            }
            k++;
        }

    }
    //copy the remaining elements
    while (i < n1){ //j = n2 
        sorted_pts[k] = L[i];
        i++;
        k++;
    }
    //may not need to do this
    while (j < n2){// i = n1
        sorted_pts[k] = R[j];
        j++;
        k++;
    }
    free(L), free(R);
    return;
}

/*	sort points according to their coordinate components	
 *	using merge sort*/
void sort(Point *sorted_pts, int l, int r, int Coordinate, int *repeat_pts){
    if (l == r)
        return;
    int m = (l + r)/2;
    sort(sorted_pts, l, m, Coordinate, repeat_pts);
    sort(sorted_pts, m+1, r, Coordinate, repeat_pts);
    merge(sorted_pts, l,m,r, Coordinate, repeat_pts);
}



ll brute_force(Point *pts, int size){
    int i, j;
    ll min_d = (ll)2*COR_MAX*COR_MAX;
    ll d;
    if (size == 2)
       return Euclidean_d2(&(pts[0]), &(pts[1]));
    for (i = 0; i < size; i++){
        for (j = i+1; j < size; j++){
            d = Euclidean_d2(&(pts[i]), &(pts[j]));
            if (d < min_d)
                min_d = d;
        } 
    }
    return min_d;
}


/*	D&C	*/
/*	X: points sorted by x-components	
 *	Y: points sorted by y-components*/
ll Closest_Pair_Dist(Point *X, Point *Y, int size){
    /*	Conquer	*/ 
    if (size <= 3){
        return brute_force(X, size); //O(3) or O(1)
    }  
    int i, j, k;
    int mid_pt = size>>1;               //the median index
    ll  m_x = X[mid_pt].x;              //the x median
    ll  m_y;
    double  delta;
    ll min_d;    //min distance square
    ll  min_d_left, min_d_right;
    ll  dist;

    vector<Point> Y_prime;
    Point *X_l = (Point*)malloc(mid_pt*sizeof(Point));
    Point *X_r = (Point*)malloc((size - mid_pt)*sizeof(Point));
    
    Point *Y_l = (Point*)malloc(mid_pt*sizeof(Point));
    Point *Y_r = (Point*)malloc((size - mid_pt)*sizeof(Point));
    
    //partition into two parts 
    for (i = 0; i < mid_pt; i++){
        X_l[i] = X[i];
    }
    for (i = 0; i < size - mid_pt; i++){
        X_r[i] = X[i + mid_pt];
    }

    j = 0, k = 0;
    for (i = 0; i < size; i++){
        if (Y[i].x < m_x){
            Y_l[j] = Y[i];
            j++;
        }
        else if (Y[i].x > m_x){ 
            Y_r[k] = Y[i];
            k++;
        }
        else{
            m_y = X[mid_pt].y;
            if (Y[i].y < m_y){
                Y_l[j] = Y[i];
                j++;
            }
            else{
                Y_r[k] = Y[i];
                k++;
            }
        } 
    }
    /*	Divide	*/
    min_d_left = Closest_Pair_Dist(X_l, Y_l, mid_pt);                   //Case1 T(N/2)
    min_d_right = Closest_Pair_Dist(X_r, Y_r, size - mid_pt);           //Case2 T(N/2)
    
    
    min_d = min(min_d_left, min_d_right);
    delta = sqrt((double)min_d);


    for (i = 0; i < size; i++){     //O(N)
        if( (double)(Y[i].x - m_x) < delta && (double)(Y[i].x - m_x) > -delta)
            Y_prime.push_back(Y[i]);
    }
    for (i = 0; i < Y_prime.size() - 1; i++){ //O(7N)
        //at most 8 points in delta*2*delta block
        for(j = i+1; j < min(i+8, Y_prime.size()); j++ ){
            dist = Euclidean_d2(&Y_prime[i], &Y_prime[j]);
            if (dist <= min_d)
               min_d = dist; 
        }
    }

    free(X_l), free(X_r);
    free(Y_l), free(Y_r);
    return min_d; 
}


int main(int argc, char *argv[]){
    int i, N;
    int repeat_pts = 0;
    ll ans;
    //int pair[2] = {0, 0};
    
    scanf("%d", &N);
    
    /*	input N 2D-coordinate cities	*/
    Point *cities   = (Point*)malloc(N*sizeof(Point));
    Point *cities_x = (Point*)malloc(N*sizeof(Point)); 
    Point *cities_y = (Point*)malloc(N*sizeof(Point));

    for (i = 0; i < N; i++){
        scanf("%d", &(cities[i].x));
        scanf("%d", &(cities[i].y));
        cities_x[i] = cities[i]; 
        cities_y[i] = cities[i];
    }
    /*	sort according to x/y - components	*/
    sort(cities_x, 0, N-1, X_coord, &repeat_pts);
    if (repeat_pts == 1){
        ans = 0;
        printf("%lld\n", ans);
        return 0;
    }
    sort(cities_y, 0, N-1, Y_coord, &repeat_pts); 
     
    //printf("Sorted\n");
    //printP(sorted_cities, N);

    ans = -Closest_Pair_Dist(cities_x, cities_y,  N);  

    printf("%lld\n", ans); 
    
    free(cities);
    free(cities_x), free(cities_y);

    return 0;
}
