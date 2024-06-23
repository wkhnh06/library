#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e5 + 5;

int n, c[N], mx[N];

vector< int > graph[N];

long long ans[N];

map< int, int > color[N];
map< int, int >::iterator it;

void dfs( int u, int p ){
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p ) continue;
        dfs( v, u );
    }
    color[u][ c[u] ]++;
    mx[ u ] = 1; ans[u] = c[u];
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p ) continue;
        if ( color[u].size() < color[v].size() ){
            color[u].swap( color[v] );
            ans[u] = ans[v];
            mx[u] = mx[v];
        }
        for ( it = color[v].begin(); it != color[v].end(); it++ ){
            int co = (*it).fi, times = (*it).se;
            color[u][co] += times;
            if ( color[u][co] > mx[u] ){
                ans[u] = co;
                mx[u] = color[u][co];
            }
            else if ( color[u][co] == mx[u] )
                ans[u] += co;
        }
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb( v );
        graph[v].pb( u );
    }
    dfs( 1, 1 );
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

