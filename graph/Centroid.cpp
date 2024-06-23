#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 50000 + 5;
const long long inf = 1e18 + 5;

int n, k, dp[N], mx;

double h, ans, Sum[N];

vector< ii > graph[N];

bool vis[N];

void dfs(int u, int p){
    dp[u] = 1;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi;
        if (v == p || vis[v]) continue;
        dfs( v, u );
        dp[u] += dp[v];
    }
}

int findcen(int u, int p, int sz){
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi;
        if (v == p || vis[v]) continue;
        if (2 * dp[v] > sz)
            return findcen( v, u, sz );
    }
    return u;
}

void findans(int u, int p, long long sum, int path, double x){
    ans = max( ans, Sum[max(k - path, 0)] + sum - (double)( x * path ) );
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi, w = graph[u][i].se;
        if ( vis[v] || v == p ) continue;
        findans(v, u, sum + w, path + 1, x);
    }
}

void update(int u, int p, long long sum, int path, double x){
    Sum[path] = max(Sum[path], sum - (double)( x * path ) );
    mx = max(mx, path);
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i].fi, w = graph[u][i].se;
        if ( vis[v] || v == p ) continue;
        update(v, u, sum + w, path + 1, x);
    }
}

void centroid(int u, double x){
    dfs(u, u);
    int cen = findcen( u, u, dp[u] );
    vis[cen] = 1;
    int lim = 0;
    for (int i = 0; i < (int)( graph[cen].size() ); i++){
        int v = graph[cen][i].fi, w = graph[cen][i].se;
        if ( vis[v] ) continue;
        findans(v, cen, w, 1, x);
        mx = 0;
        update(v, cen, w, 1, x);
        lim = max(lim, mx);
        for (int j = mx - 1; j >= 0; j--)
            Sum[j] = max( Sum[j + 1], Sum[j] );
    }
    Sum[0] = 0;
    for (int i = 1; i <= lim; i++)
        Sum[i] = -inf;
    for (int i = 0; i < (int)( graph[cen].size() ); i++){
        int v = graph[cen][i].fi;
        if ( vis[v] ) continue;
        centroid(v, x);
    }
}

double check( double x ){
    ans = -inf;
    Sum[0] = 0;
    for (int i = 1; i <= n; i++){
        vis[i] = 0;
        Sum[i] = -inf;
    }
    centroid(1, x);
    return ans;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n - 1; i++){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].pb( mp( b, c ) );
        graph[b].pb( mp( a, c ) );
    }
    double l = 0, r = 1e6 + 5, md;
    cout << setprecision(10) << fixed;
    for (int i = 1; i <= 70; i++){
        md = (l + r) / 2.0;
        if ( check( md ) >= 0 )
            l = md;
        else
            r = md;
    }
    cout << l;
}
