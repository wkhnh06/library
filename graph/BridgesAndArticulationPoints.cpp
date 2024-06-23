//https://vn.spoj.com/problems/GRAPH_/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define bp __builtin_popcountll
#define rand rd

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

typedef pair< int, int > ii;

const int N = 1e4 + 5;

int n, m, low[N], num[N], cnt, bridge, arti, par[N];

bool mark[N], vis[N];

vector< int > graph[N];

void dfs(int u, int root){
    low[u] = num[u] = ++cnt;
    vis[u] = 1;
    int child = 0;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if (!vis[v]){
            par[v] = u;
            if (u == root) ++child;
            dfs(v, root);
            low[u] = min( low[u], low[v] );
            if (num[u] < low[v])
                bridge++;
            if ( ( u == root && child >= 2) || ( u != root && num[u] <= low[v] ) )
                mark[u] = 1;
        }
        else {
            if (par[u] == v) continue;
            low[u] = min( low[u], num[v] );
        }
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i])
            dfs(i, i);
    }
    for (int i = 1; i <= n; i++)
        arti += mark[i];
    cout << arti << " " << bridge;
}
