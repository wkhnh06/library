#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;
const int N = 1e2 + 5;
const long long inf = (long long)( 1e15 );
const int Inf = (int)( 1e9 );
int n, m, K, s, t, st;

struct Edge {
    int f, cap, cost;
    Edge(){
        f = cap = cost = 0;
    }
};

vector< Edge > edge;

vector< ii > graph[N];

long long d[N];
ii prf[N];
bool inqueue[N];

queue< int > q;

bool dfs(){
    for (int i = 0; i < N; i++){
        prf[i] = mp( 0, 0 );
        inqueue[i] = 0;
        d[i] = inf;
    }
    d[s] = 0;
    q.push( s );
    while ( !q.empty() ){
        int u = q.front();
        q.pop();
        inqueue[u] = 0;
        for (int i = 0; i < (int)( graph[u].size() ); i++){
            int v = graph[u][i].fi, id = graph[u][i].se;
            if ( d[v] > d[u] + edge[id].cost && edge[id].f < edge[id].cap ){
                d[v] = d[u] + edge[id].cost;
                prf[v] = mp( u, id );
                if ( !inqueue[v] ){
                    q.push(v);
                    inqueue[v] = 1;
                }
            }
        }
    }
    return (d[t] != inf);
}

void augment(){
    int u = t, a = Inf;
    while ( u != s ){
        int id = prf[u].se;
        a = min( a, edge[id].cap - edge[id].f );
        u = prf[u].fi;
    }
    u = t;
    while ( u != s ){
        int id = prf[u].se;
        edge[id].f += a;
        edge[id ^ 1].f -= a;
        u = prf[u].fi;
    }
}

void addEdge(int u, int v, int cap, int cost){
    Edge tmp; tmp.f = 0, tmp.cap = cap, tmp.cost = cost;
    graph[u].pb( mp( v, (int)( edge.size() ) ) );
    edge.pb( tmp );
    graph[v].pb( mp( u, (int)( edge.size() ) ) );
    tmp.cap = 0; tmp.cost = -cost;
    edge.pb( tmp );

}

map< ii, ii > g;

vector< ii > E;

signed main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m >> K >> st >> t;
    s = 0;
    addEdge( s, st, K, 0 );
    for (int i = 1; i <= m; i++){
        int u, v, cost, cap;
        cin >> u >> v >> cost >> cap;
        g[ mp( u, v ) ] = mp( cost, cap );
        g[ mp( v, u ) ] = mp( cost, cap );
        E.pb( mp( u, v ) );
    }
    for (int i = m - 1; i >= 0; i--){
        int u = E[i].fi, v = E[i].se;
        if (g[ mp( u, v ) ].fi != -1){
            int cost = g[ mp( u, v ) ].fi, cap = g[ mp( u, v ) ].se;
            g[ mp( u, v ) ] = g[ mp( v, u ) ] = mp( -1, -1 );
            addEdge( u, v, cap, cost );
            addEdge( v, u, cap, cost );
        }
    }
    int flow = 0;
    long long cost = 0;
    while ( dfs() ){
        augment();
    }
    for (int i = 0; i < (int)( edge.size() ); i++){
        if ( edge[i].f > 0 )
            cost += 1ll * edge[i].f * 1ll * edge[i].cost;
    }
    for (int i = 0; i < (int)( graph[s].size() ); i++){
        int id = graph[s][i].se;
        flow += edge[id].f;
    }

    if ( flow != K ){
        cout << "-1\n";
        exit(0);
    }

    cout << cost << "\n";

    for (int i = 1; i <= n; i++){
        for (int j = 0; j < (int)( graph[i].size() ); j++){
            int v = graph[i][j].fi, id = graph[i][j].se;
            if ( edge[id].f > 0 )
                cout << i << " " << v << " " << edge[id].f << "\n";
        }
    }

    cout << "0 0 0\n";

}
/*
6 8 5 1 6
1 2 1 2
1 4 3 4
2 3 1 4
2 5 5 2
3 4 2 4
3 6 1 2
4 6 4 1
5 6 6 2
*/
