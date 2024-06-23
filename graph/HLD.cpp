#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

const int N = 1e5  + 5;

int n, q, it[4 * N], lz[4 * N], lca[N][20], child[N], h[N], cnt, pos[N], st[N], en[N], num, head[N], part[N];

vector<int> graph[N];

void initlca(){
    for (int j = 1; j <= 18; j++){
        for (int i = 1; i <= n; i++)
            lca[i][j] = lca[lca[i][j - 1]][j - 1];
    }
}

int findlca(int u, int v){
    if (h[u] < h[v]) swap(u, v);
    for (int i = 18; i >= 0; i--){
        if (lca[u][i] != 0 && h[lca[u][i]] >= h[v])
            u = lca[u][i];
    }
    if (u == v) return u;
    for (int i = 18; i >= 0; i--){
        if (lca[u][i] != 0 && lca[v][i] != 0 && lca[u][i] != lca[v][i]){
            u = lca[u][i];
            v = lca[v][i];
        }
    }
    return lca[u][0];
}

void dfs(int u, int p){
    child[u] = 1;
    for (int i = 0; i < graph[u].size(); i++){
        int v = graph[u][i];
        if (v == p) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
        lca[v][0] = u;
        child[u] += child[v];
    }
}

void hld(int u, int p){
    if (!head[num])
        head[num] = u;
    pos[u] = st[u] = ++cnt;
    part[u] = num;
    int mx = -1, id = -1;
    for (int i = 0; i < graph[u].size(); i++){
        int v = graph[u][i];
        if (v == p) continue;
        if (child[v] > mx){
            mx = child[v];
            id = v;
        }
    }
    if (id != -1)
        hld(id, u);
    for (int i = 0; i < graph[u].size(); i++){
        int v = graph[u][i];
        if (v == p || v == id) continue;
        num++;
        hld(v, u);
    }
    en[u] = cnt;
}

void lzupdate(int k, int l, int r){
    it[k] += lz[k];
    if (l != r){
        lz[k << 1] += lz[k];
        lz[k << 1 | 1] += lz[k];
    }
    lz[k] = 0;
}

void update(int k, int l, int r, int L, int R, int val){
    lzupdate(k, l, r);
    if (r < L || R < l || L > R) return ;
    if (L <= l && r <= R){
        lz[k] += val;
        lzupdate(k, l, r);
        return ;
    }
    int mid = (l + r) >> 1;
    update(k << 1, l, mid, L, R, val);
    update(k << 1 | 1, mid + 1, r, L, R, val);
    it[k] = max(it[k << 1], it[k << 1 | 1]);
}

int get(int k, int l, int r, int L, int R){
    lzupdate(k, l, r);
    if (r < L || R < l || L > R) return INT_MIN;
    if (L <= l && r <= R)
        return it[k];
    int mid = (l + r) >> 1;
    return max(get(k << 1, l, mid, L, R), get(k << 1 | 1, mid + 1, r, L, R));
}

void gethld(int u, int v){
    int node = findlca(u, v), a = INT_MIN;
    while (part[u] != part[node]){
        a = max(a, get(1, 1, n, pos[head[part[u]]], pos[u]));
        u = lca[head[part[u]]][0];
    }
    a = max(a, get(1, 1, n, pos[node], pos[u]));
    while (part[v] != part[node]){
        a = max(a, get(1, 1, n, pos[head[part[v]]], pos[v]));
        v = lca[head[part[v]]][0];
    }
    a = max(a, get(1, 1, n, pos[node], pos[v]));
    cout << a << "\n";
}

int main(){
    cin.tie(0), ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n - 1; i++){
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    dfs(1, 1);
    initlca();
    hld(1, 1);
    cin >> q;
    while (q--){
        string s;
        cin >> s;
        if (s == "add"){
            int u, val;
            cin >> u >> val;
            update(1, 1, n, st[u], en[u], val);
        }
        else{
            int u, v;
            cin >> u >> v;
            gethld(u, v);
        }
    }
}

