#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 15;

int n, m, low[N], num[N], cnt, par[N];

stack< ii > st;

vector< int > graph[N];

bool vis[N];

vector< vector< ii > > edge;

void dfs(int u, int root){
    low[u] = num[u] = ++cnt;
    int child = 0;
    vis[u] = 1;
    for (int i = 0; i < (int)( graph[u].size() ); i++){
        int v = graph[u][i];
        if (!vis[v]){
            child++;
            st.push( mp( u, v ) );
            par[v] = u;
            dfs(v, root);
            low[u] = min(low[u], low[v]);
            if ( ( u == root && child >= 2 ) || ( u != root && num[u] <= low[v] ) ){
                vector< ii > temp;
                while ( st.top().fi != u || st.top().se != v ){
                    temp.pb( st.top() );
                    st.pop();
                }
                temp.pb( mp(u, v) );
                st.pop();
                edge.pb(temp);
            }
        }
        else {
            if (par[u] == v) continue;
            if (num[v] < num[u])
                st.push( mp( u, v ) );
            low[u] = min(low[u], num[v]);
        }
    }
}

bool used[N];

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
        if (!vis[i]){
            dfs(i, i);
            if ( st.size() ){
                vector< ii > temp;
                while ( !st.empty() ){
                    temp.pb( st.top() );
                    st.pop();
                }
                edge.pb(temp);
            }
        }
    }
    int Odd = 0, Even = 0;
    for (int i = 0; i < (int)( edge.size() ); i++){
        vector< ii > temp = edge[i];
        int sum = 0;
        memset(used, 0, sizeof(used));
        for (int j = 0; j < (int)( temp.size() ); j++){
            if (!used[ temp[j].fi ]){
                sum++;
                used[ temp[j].fi ] = 1;
            }
            if (!used[ temp[j].se ]){
                sum++;
                used[ temp[j].se ] = 1;
            }
        }
        if (sum % 2)
            Odd++;
        else
            Even++;
    }
    cout << Odd << " " << Even << "\n";
}
