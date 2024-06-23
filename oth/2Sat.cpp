#include<bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define sz(x) ( (int)(x).size() )
#define fi first
#define se second
using LL = long long;

int n, nPar, iTime, nSCC;
stack<int> st;
vector<bool> inSt;
vector<int> disc, low, inSCC;
vector<vector<int> > gr;

int getId(int i, char col){ return col == 'B' ? i << 1 : i << 1 | 1; }

void addEdge(int u, int v){
    gr[u ^ 1].emplace_back(v);
    gr[v ^ 1].emplace_back(u);
}

void dfs(int u){
    disc[u] = low[u] = ++iTime;
    st.emplace(u); inSt[u] = true;

    for (int v : gr[u]){
        if (!disc[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inSt[v]) low[u] = min(low[u], disc[v]);
    }

    if (low[u] == disc[u]){
        while (st.top() != u){
            inSCC[st.top()] = nSCC;
            inSt[st.top()] = false; st.pop();
        }
        inSCC[st.top()] = nSCC;
        inSt[st.top()] = false; st.pop();

        ++nSCC;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> nPar;

    gr.assign(n << 1, {} );
    while (nPar--){
        array<pair<int, char>, 3> cur;
        for (int i = 0; i < 3; ++i){
            cin >> cur[i].fi >> cur[i].se; 
            --cur[i].fi;
            for (int j = 0; j < i; ++j) 
                addEdge(getId(cur[i].fi, cur[i].se), getId(cur[j].fi, cur[j].se) );
        }
    }

    disc.assign(sz(gr), 0);
    low.assign(sz(gr), 0);
    inSt.assign(sz(gr), false);
    inSCC.assign(sz(gr), -1);
    for (int u = 0; u < sz(gr); ++u) 
        if (!disc[u]) 
            dfs(u);

    for (int u = 0; u < n; ++u) 
        if (inSCC[getId(u, 'B')] == inSCC[getId(u, 'R')]) 
            return cout << "-1\n", 0;

    vector<char> ans(n);
    for (int u = 0; u < n; ++u) 
        ans[u] = inSCC[getId(u, 'B')] < inSCC[getId(u, 'R')] ? 'B' : 'R';
    for (auto c : ans) 
        cout << c;
    cout << '\n';

    return 0;
}

