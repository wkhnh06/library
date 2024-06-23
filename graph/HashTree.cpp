#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;
#define rand rd
mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 1e9 + 9;

const int N = 4005;

int n, dp[N], pw[N], d[N];

vector< int > graph[N], cen;

int addup( int x, int y ){
    return (1ll * x + 1ll * y) % mod;
}

int subs( int x, int y ){
    return ( (1ll * x - 1ll * y) % mod + mod ) % mod;
}

int mul( int x, int y ){
    return (1ll * x * 1ll * y) % mod;
}

void dfs( int u, int p ){
    dp[u] = 1;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p ) continue;
        dfs( v, u );
        dp[u] += dp[v];
    }
}

void findcen( int u, int p, int sz ){
    bool is_centroid = 1;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p ) continue;
        if ( dp[v] > sz / 2 )
            is_centroid = 0;
        findcen( v, u, sz );
    }
    if ( sz - dp[u] > sz / 2 )
        is_centroid = 0;
    if ( is_centroid )
        cen.pb( u );
}

int geths( int u, int p, int root ){
    d[u] = 0;
    vector< int > tmp;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p || v == root ) continue;
        tmp.pb( geths( v, u, root ) );
        d[u] = max( d[u], d[v] + 1 );
    }
    int val = 1;
    for (int i = 0; i < (int)( tmp.size() ); i++)
        val = mul( val, addup( pw[ d[u] ], tmp[i] ) );
    return val;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    for (int i = 0; i < N; i++)
        pw[i] = mul( rand(), rand() );
    cin >> n;
    for (int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb( v );
        graph[v].pb( u );
    }
    dfs( 1, 1 );
    findcen( 1, 1, dp[1] );
    int root = cen[0]; 
    int value = -1;
    for (int i = 0; i < (int)( graph[root].size() ); i++){
        int v = graph[root][i];
        cen.clear();
        dfs( v, root );
        findcen( v, root, dp[v] );
        int tmp = geths( cen[0], cen[0], root );
        if ( cen.size() > 1 )
            tmp = min( tmp, geths( cen[1], cen[1], root ) );
        if ( value == -1 )
            value = tmp;
        else if ( value != tmp ){
            cout << "-1\n";
            exit(0);
        }
    }
    cout << graph[root].size();
}

