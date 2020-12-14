#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))

/*	undirected weighted tree 	*/
typedef struct Vertex{
    int state;
    ll  d;
}Vertex;
/*	undirected	*/
typedef struct Edge{
    int from, to;
    int weight;
}Edge;
class Graph{
    int         V_num;
    int         E_num;
    Vertex      *V;
    list<Edge>  *Adj;
    ll          *ans;
    ll          d_max;
    int         farthest;
    vector<ll>  H;
public:
    Graph(int V_num, int E_num){
        this->V_num = V_num, this->E_num = E_num;
        V   = new Vertex[V_num+1];
        Adj = new list<Edge>[V_num+1];
        ans = new ll[V_num+1];
    }
    ~Graph(){
        delete [] V;
        delete [] Adj;
        delete [] ans;
    }
    void addEdge(int u, int v, ll w);
    void getEdges();
    void dfs1_visit(int u);
    void dfs2_visit(int u);
    void dfs(int start, int flag);
    void solve();
};
/*	undirected graph	*/
void Graph::addEdge(int u, int v, ll w){
    Edge e1, e2;
    e1.from = u, e1.to = v, e1.weight = w;
    e2.from = v, e2.to = u, e2.weight = w;
    Adj[u].push_back(e1), Adj[v].push_back(e2); 
    return;
}
void Graph::getEdges(){
    int u, v; ll w;
    for (int i = 0; i < E_num; ++i){
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u,v,w);
    }
    return;
}
void Graph::dfs1_visit(int u){
    /*	V[u].d : the longest distance from start 	*/
    ll dist;
    V[u].state = 1;
    for (auto e : Adj[u]){
        if (!V[e.to].state){
            V[e.to].d = V[u].d + e.weight;
            if (V[e.to].d > d_max){
                d_max = V[e.to].d, farthest = e.to;
            }
            dfs1_visit(e.to);
        }
    }
    return;
}
void Graph::dfs2_visit(int u){
    /*	V[u].d : the longest distance that ends at u	*/
    ll dist;
    V[u].state = 1;
    for (auto e : Adj[u]){
        if (!V[e.to].state){
            dfs2_visit(e.to);
            dist = V[e.to].d + e.weight;  
            if (dist > V[u].d){
                H.push_back(V[u].d);
                push_heap(H.begin(), H.end());
                V[u].d = dist;
            }
            else{
                H.push_back(dist);
                push_heap(H.begin(), H.end()); 
            }
        }
    }
    return;
}
void Graph::dfs(int start, int flag){
    for (int i = 1; i < V_num+1; ++i){
        V[i] = {};
    }  
    if (flag == 1){
        farthest = 0, d_max = 0;
        dfs1_visit(start);
    }
    else if (flag == 2){
        make_heap(H.begin(), H.end());
        dfs2_visit(start);
        d_max = V[start].d; /*	this is diameter	*/
    }
    return;
}
void Graph::solve(){
    getEdges();
    /*	find end edge	*/
    dfs(1, 1);          /*	dfs1_visit	*/
    dfs(farthest, 2);   /*	dfs2_visit	*/
    
    for (int k = 1; k < V_num+1; ++k){
        if (k == 1)
            ans[k] = 0;
        else if (k == 2)
            ans[k] = d_max;
        else{
            if (H.front()){
                ans[k] = ans[k-1] + H.front();
                pop_heap(H.begin(), H.end());
                H.pop_back();
            }
            else{
                ans[k] = ans[k-1];
            }
        }
    }
    for (int k = 1; k < V_num+1; ++k){
        printf("%lld ", ans[k]);
    }
    printf("\n");
    return;
}
int main(int argc, char *argv[]){
    int n;
    scanf("%d",&n);
    Graph G(n,n-1);
    G.solve();
    return 0;
}
