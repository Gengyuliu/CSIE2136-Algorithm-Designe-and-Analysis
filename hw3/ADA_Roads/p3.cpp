#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <list>
#include <utility>
using namespace std;
#define ll long long
#define MAX 300000000000001
#define mem(a,b) memset(a,b,sizeof(a))
typedef struct Vertex{
    int root, ranking;
    ll d;
}Vertex;
typedef struct Edge{
    int from, to;
    ll w;
}Edge;

class Graph{
    int V_num, E_num;
    Vertex *V; Edge *E;
    int S, T;
    ll  *_max;
    list<Edge> *Adj;
public:
    Graph(int V_num, int E_num, int S, int T){
        this->V_num = V_num, this->E_num = E_num, this->S = S, this->T = T;
        V   = new Vertex[V_num+1], E = new Edge[E_num];
        Adj = new list<Edge>[V_num+1];
        _max = new ll[V_num+1];
    }
    ~Graph(){
        delete[] V, delete [] E, delete[] Adj, delete[] _max;
    }
    void initVertex(){
        for (int i = 0; i < V_num+1; ++i){
            V[i].root = i, V[i].ranking = 0, V[i].d = MAX;
        }    
    }
    void addEdge(int from, int to, ll w){
        Edge e1, e2;
        e1.from = from, e1.to = to, e1.w = w;
        e2.from = to, e2.to = from, e2.w = w;
        Adj[from].push_back(e1), Adj[to].push_back(e2);
    }
    void getEdges(){
        for (int i = 0; i < E_num; ++i){
            scanf("%d %d %lld", &E[i].from, &E[i].to, &E[i].w);
            //addEdge(E[i].from, E[i].to, E[i].w);
        } 
    }
    int findSet(int x){
        if (V[x].root != x)
            V[x].root = findSet(V[x].root);
        return V[x].root;
    }
    void Union(int x, int y){
        int root_x = findSet(x), root_y = findSet(y);
        if (root_x == root_y)
            return;
        V[root_y].root = root_x; 
        return;
    }
    static bool cmp_mst(Edge a, Edge b){
        return a.w < b.w;
    }
    static bool cmp_sp(pair<int,ll> a, pair<int,ll> b){
        return a.second > b.second;
    }
    void relax(int u, int v, ll w, vector<pair<int,ll>> &Q){
        if (V[v].d > V[u].d + w){
            V[v].d = V[u].d + w;
            pair<int,ll> node = make_pair(v, V[v].d);
            Q.push_back(node), push_heap(Q.begin(), Q.end(), cmp_sp);
        } 
    }
    void Kruskal_MST();
    void Dijkstra(int s);
    void run();
};

void Graph::Kruskal_MST(){
    int x, y;
    mem(_max,0);
    sort(E, E+E_num, cmp_mst);
    for (int i=0; i < E_num; ++i){
        x = findSet(E[i].from), y = findSet(E[i].to);
        if (x != y){
            //mst.push_back(E[i]);
            addEdge(E[i].from, E[i].to, E[i].w);
            Union(x, y);
            _max[x] = max(_max[x], E[i].w);
        }
        else if (x == y && E[i].w <= _max[x]){
            //mst.push_back(E[i]);
            addEdge(E[i].from, E[i].to, E[i].w);
            _max[x] = max(_max[x], E[i].w);
        }
    }
}

void Graph::Dijkstra(int s){
    V[s].d = 0;
    int u;
    pair<int,ll> src = make_pair(s, V[s].d);
    vector<pair<int,ll>> Q; /*	a min heap	*/
    
    Q.push_back(src);
    make_heap(Q.begin(), Q.end(), cmp_sp) ;
    for (;!Q.empty();){
        pair<int,ll> node = Q.front(); u = node.first;
        pop_heap(Q.begin(), Q.end(), cmp_sp) ;
        Q.pop_back();
        for (auto e : Adj[u]){
            relax(u, e.to, e.w, Q);
        }
    }
     
}
void Graph::run(){
    initVertex(); getEdges();
    Kruskal_MST();
    Dijkstra(S);
    printf("%lld\n", V[T].d);
}
int main(int argc, char *argv[]){
    int N, M, S, T;
    scanf("%d %d %d %d", &N, &M, &S, &T);
    Graph G(N,M,S,T);
    G.run();
    return 0;
}

