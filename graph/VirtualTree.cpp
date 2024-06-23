#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef pair< int, int > ii;

const int mod = 1e9 + 7;

const int inf = 1e9;

int add( int x, int y ){
    return ( 1ll * x + 1ll * y ) % mod;
}

int mul( int x, int y ){
    return ( 1ll * x * 1ll * y ) % mod;
}

int del( int x, int y ){
    return ( ( 1ll * x - 1ll * y ) % mod + mod ) % mod;
}

const int N = 1e5 + 5;

int n, f[N], par[N][20], st[N], cnt, dp[N][2], import[N];

vector< int > graph[N], g[N];

void dfs( int u, int p ){
    st[u] = ++cnt;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if ( v == p ) continue;
        f[v] = f[u] + 1;
        dfs( v, u );
        par[v][0] = u;
    }
}

void initlca(){
    for (int j = 1; j < 20; j++){
        for (int i = 1; i <= n; i++)
            par[i][j] = par[ par[i][j - 1] ][j - 1];
    }
}

int findlca( int u, int v ){
    if ( f[u] < f[v] ) swap( u, v );
    for (int j = 19; j >= 0; j--){
        if ( par[u][j] != 0 && f[ par[u][j] ] >= f[v] )
            u = par[u][j];
    }
    if ( u == v ) return u;
    for (int j = 19; j >= 0; j--){
        if ( par[u][j] != 0 && par[v][j] != 0 && par[u][j] != par[v][j] ){
            u = par[u][j];
            v = par[v][j];
        }
    }
    return par[u][0];
}

void solve( int u, int p ){
    for (int i = 0; i < (int)( g[u].size() ); i++){
        int v = g[u][i];
        if ( v == p ) continue;
        solve( v, u );
    }
    if ( import[u] ){
        dp[u][0] = inf;
        int cur = 0;
        for (int i = 0; i < (int)( g[u].size() ); i++){
            int v = g[u][i];
            if ( v == p ) continue;
            int tmp = dp[v][0];
            if ( !import[v] )
                tmp = min( tmp, dp[v][1] + 1);
            if ( import[v] && f[v] - f[u] >= 2 )
                tmp = min( tmp, dp[v][1] + 1);
            if ( import[v] && f[v] - f[u] == 1 )
                tmp = inf;
            cur += tmp;
            cur = min( cur, inf );
        }
        dp[u][1] = cur;
    }
    else {
        int cur0 = 0, cur1 = inf, cutall = 0;
        int ok = 0;
        for (int i = 0; i < (int)( g[u].size() ); i++){
            int v = g[u][i];
            if ( v == p ) continue;
            cutall += min( dp[v][0], dp[v][1] );
            cutall = min( cutall, inf );
        }
        cutall = min( cutall + 1, inf );
        for (int i = 0; i < (int)( g[u].size() ); i++){
            int v = g[u][i];
            if ( v == p ) continue;
            int tmp0 = dp[v][0];
            if ( !import[v] )
                tmp0 = min( tmp0, dp[v][1] + 1);
            if ( import[v] && f[v] - f[u] >= 2 )
                tmp0 = min( tmp0, dp[v][1] + 1);
            if ( import[v] && f[v] - f[u] == 1 )
                ok++;
            int tmp1 = cur1;
            cur1 = min( cur0 + dp[v][1] , tmp1 + tmp0 );
            cur0 += tmp0;
            cur0 = min( cur0, inf );
            cur1 = min( cur1, inf );
        }
        if ( ok >= 2 ){
            dp[u][0] = cutall;
            dp[u][1] = inf;
        }
        else if ( ok == 1 ){
            dp[u][0] = cutall;
            for (int i = 0; i < (int)( g[u].size() ); i++){
                int v = g[u][i];
                if ( v == p ) continue;
                if ( import[v] && f[v] - f[u] == 1 )
                    dp[u][1] += dp[v][1];
                else
                    dp[u][1] += min( dp[v][1] + 1, dp[v][0] );
                dp[u][1] = min( inf, dp[u][1] );
            }
        }
        else {
            dp[u][0] = min( cutall, cur0 );
            dp[u][1] = cur1;
        }
    }
}

vector< ii > tree;

stack< int > S;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb( v );
        graph[v].pb( u );
    }
    dfs( 1, 1 );
    initlca();
    int q;
    cin >> q;
    while ( q--  ){
        int num;
        cin >> num;
        for (int i = 1; i <= num; i++){
            int u;
            cin >> u;
            tree.pb( mp( st[u], u ) );
            import[u] = 1;
        }
        sort( tree.begin(), tree.end() );
        tree.erase( unique( tree.begin(), tree.end() ), tree.end() );
        for (int i = 0; i < num - 1; i++){
            int lca = findlca( tree[i].se, tree[i + 1].se );
            tree.pb( mp( st[lca], lca ) );
        }
        sort( tree.begin(), tree.end() );
        tree.erase( unique( tree.begin(), tree.end() ), tree.end() );
        int m = (int)( tree.size() );
        for (int i = m - 1; i >= 0; i--){
            while ( !S.empty() && findlca( S.top(), tree[i].se ) == tree[i].se ){
                g[ S.top() ].pb( tree[i].se );
                g[ tree[i].se ].pb( S.top() );
                S.pop();
            }
            S.push( tree[i].se );
        }
        solve( tree[0].se, tree[0].se );
        int ans = min( dp[tree[0].se][0], dp[tree[0].se][1] );
        if ( ans >= inf )
            cout << "-1\n";
        else
            cout << ans << "\n";
        while ( !S.empty() ) S.pop();
        for (int i = 0; i < m; i++){
            g[ tree[i].se ].clear();
            import[ tree[i].se ] = 0;
            dp[ tree[i].se ][0] = dp[ tree[i].se ][1] = 0;
        }
        tree.clear();
    }
}
/*
4
1 3
2 3
4 3
4
2 1 2
3 2 3 4
3 1 2 4
4 1 2 3 4
*/

