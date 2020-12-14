#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>
#include <stack>
#include <list>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
typedef struct Vertex{
    int id;         /*	dfs order (id)	*/
    int low;
    ll  weight;
}Vertex;
/*	from---weight--->to	*/
typedef struct Edge{
    int to;
    ll  weight; 
}Edge;

class Graph{
    int             dfs_cnt;    /*	count # of dfs	*/
    int             scc_cnt;    /*	count # of SCCs	*/
    int             V_num;
    int             E_num;
    int             SCC_num;    /*	# of SCCs	*/
    Vertex          *V;
    list<Edge>      *Adj;
    int             *DFS_ordr;  /*	map the dfs order to vertex id	*/
    int             *SCC_id;    /*	map vertex id to SCC id	*/
    ll              *SCC_w;     /*	the weights of SCC	*/
    list<Edge>      *SCC_Adj;   /*	SCC's Adj	*/ 
    int             *SCC_state;
    ll              *dist;
    stack<int>      S;          /*	Stack-invariant	*/
    int             *onS;
public:
    Graph(int V_num, int E_num){
        this->V_num = V_num, this->E_num = E_num;
        V       = new Vertex[V_num+1]; 
        Adj     = new list<Edge>[V_num+1]; 
        DFS_ordr= new int[V_num+1]; 
        SCC_id  = new int[V_num+1];
        SCC_w   = new ll[V_num+1];
        SCC_Adj = new list<Edge>[V_num+1];
        SCC_state = new int[V_num+1];
        dist    = new ll[V_num+1];      /*	the longest possible dist from u	*/
        onS     = new int[V_num+1];
    }
    ~Graph(){
        delete [] V; delete [] Adj; delete [] DFS_ordr;
        delete [] SCC_id; delete [] SCC_w, delete [] SCC_Adj;
        delete [] dist; delete [] onS, delete [] SCC_state;
    }
    void    getVertices();
    void    addEdge(int from, int to, ll weight); 
    void    getEdges();
    void    DFS();
    void    DFS_visit(int scc_u);
    int     findLow(int x);
    void    Tarjan_SCC();
    void    find_SCC(int u);
    void    build_SCC();
    void    run();
};

void Graph::getVertices(){
    int i;
    for (i = 1; i < V_num+1; ++i){
        V[i] = {};
        scanf("%lld", &V[i].weight);
    }
    return;
}
/*	from --weight--> to	*/
void Graph::addEdge(int from, int to, ll weight){
    Edge e;
    e.to = to, e.weight = weight;
    Adj[from].push_back(e);
    return;
}
void Graph::getEdges(){
    int from, to;
    ll w;
    for (int i = 0; i < E_num; ++i){
        scanf("%d %d %lld", &from, &to, &w); 
        addEdge(from, to, w);
    }
    return;
}
/*	O(V+E)	*/
void Graph::DFS_visit(int scc_u){
    SCC_state[scc_u] = 1;
    dist[scc_u] = SCC_w[scc_u];
    for (auto e : SCC_Adj[scc_u]){
        if (!SCC_state[e.to]){
            DFS_visit(e.to);
        }
        dist[scc_u] = max(dist[scc_u], SCC_w[scc_u]+e.weight+dist[e.to]);
    }
    return;
}
void Graph::DFS(){
    mem(SCC_state, 0); //mem(dist,0);
    for (int scc_u = 1; scc_u < scc_cnt+1; ++scc_u){
        if (!SCC_state[scc_u]){
            DFS_visit(scc_u); 
        }
    }
    return;
}
int Graph::findLow(int u){
    int u_pre;
    if (V[u].low != V[u].id){
        u_pre = DFS_ordr[V[u].low]; 
        V[u].low = findLow(u_pre);
    }
    return V[u].low;
}

/*	identifying the SCCs	*/
void Graph::find_SCC(int u){
    V[u].id = V[u].low = ++dfs_cnt;
    S.push(V[u].id), onS[V[u].id] = 1;
    DFS_ordr[V[u].id] = u;
    for (auto e : Adj[u]){
        if (!V[e.to].id){
            find_SCC(e.to);
            /*	tree edge	*/
            //V[u].low = min(V[u].low, V[e.to].low);
        }
        
        if (onS[V[e.to].id]){
            /*	back edge	*/
            V[u].low = min(V[u].low, V[e.to].low);    
        }
    }
    if (V[u].low == V[u].id){
        ++scc_cnt;
        for (;;){
            int id=S.top(); S.pop(); onS[id]=0;
            int v=DFS_ordr[id]; 
            SCC_id[v] = scc_cnt;
            SCC_w[scc_cnt] += V[v].weight;
            for (auto e : Adj[v]){
                if (V[e.to].low == V[u].low || findLow(e.to) == V[u].low)
                    SCC_w[scc_cnt] += e.weight;
            }
            if (id == V[u].id)
                break;
        }
    }
    return;
}
/*	O(V+E)	*/
void Graph::Tarjan_SCC(){
    mem(DFS_ordr,0);
    mem(onS,0), mem(SCC_id,0), mem(SCC_w,0), dfs_cnt = scc_cnt = 0;
    for (int u = 1; u < V_num+1; ++u){
        if (!V[u].id){
            find_SCC(u);
        } 
    } 
    return;     
}
/*	O(V+E)	*/
void Graph::build_SCC(){
    for (int u=1; u < V_num+1; ++u){
        for (auto e : Adj[u]){
            if (SCC_id[u] != SCC_id[e.to]){
                Edge scc_e;
                scc_e.to=SCC_id[e.to], scc_e.weight = e.weight;  
                SCC_Adj[SCC_id[u]].push_back(scc_e);
            }
        }
    } 
    return;
}
void Graph::run(){
    ll  ans = (ll)-1;
    getVertices();
    getEdges();
    Tarjan_SCC();
    build_SCC(); 
    DFS();
    for (int i = 1; i < scc_cnt+1; ++i){
        ans = max(dist[i], ans);
    }
    printf("%lld\n", ans);
    return;
}
int main(int argc, char *argv[]){
    int i, j;
    int N, M;
    scanf("%d %d", &N, &M);
    Graph G(N, M);
    G.run();
    return 0;
}
