#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

const int mod = 1e9 + 7;
const int inf = 1e9;

int add(int x, int y){
    return (1ll * x + 1ll * y) % mod;
}

int mul(int x, int y){
    return (1ll * x * 1ll * y) % mod;
}

int del(int x, int y){
    return ((1ll * x - 1ll * y) % mod + mod) % mod;
}

const int N = 35;

int test, n, m, a[N][N], lmao[N * N];

bitset<N * N> name[N * N];

int id(int x, int y){
    return (x - 1) * m + y;
}

int check(int x, int y){
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int gauss(){
    int cur = 1;
    for (int i = 1; i <= n * m; i++){
        for (int j = cur; j <= n * m; j++){
            if (lmao[j] != -1 && name[j][i]){
                swap(name[j], name[cur]);
                swap(lmao[j], lmao[cur]);
                for (int k = 1; k <= n * m; k++){
                    if (k != cur && name[k][i] && lmao[k] != -1){
                        name[k] ^= name[cur];
                        lmao[k] ^= lmao[cur];
                    }
                }
                ++cur;
                break;
            }
        }
    }
    int cur1 = 1;
    for (int i = 1; i <= n * m; i++){
        if (lmao[i] == -1) cur1 = mul(cur1, 2);
        else if (name[i].count() == 0 && lmao[i] == 1) cur1 = mul(cur1, 0);
        else if (name[i].count() == 0) cur1 = mul(cur1, 2);
    }
    return cur1;
}

int main(){
    cin.tie(0), ios::sync_with_stdio(0);
    cin >> test;
    while (test--){
        cin >> n >> m;
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        }
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                name[id(i, j)].reset();
                lmao[id(i, j)] = a[i][j];
            }
        }
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                for (int k = 0; k < 4; k++){
                    if (check(i + dx[k], j + dy[k]) && a[i][j] >= 0)
                        name[id(i, j)][id(i + dx[k], j + dy[k])] = 1;
                }
            }
        }
        cout << gauss() << "\n";
    }
}
