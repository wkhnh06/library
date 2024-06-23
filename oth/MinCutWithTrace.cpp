#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e3 + 5;

const long long infll = (long long)( 1e15 );
const int inf = (int)( 1e9 + 5 );
int d[ 2 * N ];
int prf[ 2 * N ], s, t, n, m;

vector< ii > graph[ 2 * N ];

struct Edge {
    int f, cap;
    Edge(){
        f = 0, cap = 0;
    }
};

vector< Edge > edge;

queue< int > q;

bool dfs(){
    for (int i = 0; i <= t; i++)
        d[i] = inf, prf[i] = 0;
    q.push( s );
    d[s] = 0;
    while ( !q.empty() ){
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)( graph[u].size() ); i++){
            int v = graph[u][i].fi, id = graph[u][i].se;
            if ( d[v] > d[u] + 1 && edge[id].f < edge[id].cap ){
                d[v] = d[u] + 1;
                q.push( v );
            }
        }
    }
    return (d[t] != inf);
}

int augment(int u, int flow){
    if ( u == t || !flow) return flow;
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
    Edge tmp; tmp.cap = cap;
    int sz = (int)( edge.size() );
    graph[u].pb( mp( v, sz ) );
    edge.pb( tmp );
    sz = (int)( edge.size() );
    graph[v].pb( mp( u, sz ) );
    tmp.cap = 0;
    edge.pb( tmp );
}

bool vis[2 * N];

void bfs(int u){
    vis[u] = 1;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi, id = graph[u][i].se;
        if ( edge[id].f < edge[id].cap && !vis[v] )
            bfs(v);
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m;
    s = 0; t = 2 * n + 1;
    for (int i = 1; i <= n; i++){
        int type, c;
        cin >> type >> c;
        addEdge( m + i, t, c );
    }
    long long sum = 0;
    for (int i = 1; i <= m; i++){
        int a, b, c, w;
        cin >> a >> b >> c >> w;
        sum += w;
        addEdge( s, i, w );
        addEdge( i, m + a, inf );
        addEdge( i, m + b, inf );
        addEdge( i, m + c, inf );
    }
    while ( dfs() ){
        while ( augment( s, inf ) ){
        }
    }
    for (int i = 0; i < m; i++){
        int id = graph[s][i].se;
        sum -= edge[id].f;
    }
    int cnt = 0;
    bfs(s);
    for (int i = m + 1; i <= n + m; i++){
        if ( vis[i] )
            cnt++;
    }
    cout << sum << " " << cnt << "\n";
    for (int i = m + 1; i <= n + m; i++){
        if ( vis[i] )
            cout << i - m << " ";
    }
}

