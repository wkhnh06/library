#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

#define int long long

typedef pair<int, int> ii;

const int N = 1e4 + 5;

int n, m, sum;

bool mark[N];

vector<ii> graph[N];

priority_queue<ii, vector<ii>, greater<ii>> pq;

signed main(){
    cin.tie(0), ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        graph[u].pb({c, v});
        graph[v].pb({c, u});
    }
    pq.push({0, 1});
    while (!pq.empty()){
        ii frt = pq.top();
        pq.pop();
        int u = frt.se;
        if (mark[u]) continue;
        sum += frt.fi;
        mark[u] = 1;
        for (int i = 0; i < graph[u].size(); i++){
            ii v = graph[u][i];
            if (mark[v.se] == 0)
                pq.push({v});
        }
    }
    cout << sum;
}

