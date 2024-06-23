//https://vn.spoj.com/problems/TJALG/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e4 + 5;

int n, m, stmem[N], vis[N], cnt, low[N], num[N], ans;

stack< int > st;

vector< int > graph[N];

void dfs(int u){
    low[u] = num[u] = ++cnt;
    vis[u] = 1;
    stmem[u] = 1;
    st.push(u);
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if (!vis[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (stmem[v])
            low[u] = min(low[u], num[v]);
    }
    if (low[u] == num[u]){
        while (!st.empty() && st.top() != u){
            stmem[ st.top() ] = 0;
            st.pop();
        }
        stmem[u] = 0;
        st.pop();
        ans++;
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i])
            dfs(i);
    }
    cout << ans;
}
