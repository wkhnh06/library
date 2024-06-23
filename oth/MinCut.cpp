#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 255;

const int inf = 1e9;

int n, s, t, d[N], prf[N];

vector< ii > graph[N];

queue< int > q;

struct Edge {
    int f, cap;
    Edge(){
        f = cap = 0;
    }
};

vector< Edge > edge;

bool dfs(){
    for (int i = 0; i <= t; i++){
        d[i] = inf, prf[i] = 0;
    }
    d[s] = 0;
    q.push(s);
    while ( !q.empty() ){
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)( graph[u].size() ); i++){
            int v = graph[u][i].fi, id = graph[u][i].se;
            if ( d[v] > d[u] + 1 && edge[id].f < edge[id].cap ){
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return ( d[t] != inf );
}

int augment(int u, int flow){
    if (u == t || !flow) return flow;
    for (int &i = prf[u]; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi, id = graph[u][i].se;
        if ( edge[id].f >= edge[id].cap ) continue;
        if ( d[v] != d[u] + 1 ) continue;
        int nxt = augment( v, min( flow, edge[id].cap - edge[id].f ) );
        if ( nxt ){
            edge[id].f += nxt;
            edge[id ^ 1].f -= nxt;
            return nxt;
        }
    }
    return 0;
}

void addEdge(int u, int v, int cap){
    Edge tmp; tmp.f = 0, tmp.cap = cap;
    graph[u].pb( mp( v, (int)( edge.size() ) ) );
    edge.pb( tmp );
    graph[v].pb( mp( u, (int)( edge.size() ) ) );
    tmp.cap = 0;
    edge.pb( tmp );
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    s = 0, t = n + 1;
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        addEdge( s, i, x );
    }
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        addEdge( i, t, x );
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            int x;
            cin >> x;
            addEdge( i, j, x );
        }
    }
    while ( dfs() ){
        while ( augment( s, inf ) ){
        }
    }
    int flow = 0;
    for (int i = 0; i < (int)( graph[s].size() ); i++){
        int id = graph[s][i].se;
        flow += edge[id].f;
    }
    cout << flow;
}

