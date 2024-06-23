#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;
const long long infll = (long long)(1e15);

const int N = 2e3 + 5;

long long f[N][N], pre[N];

int n, a[N], best[N][N];

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++)
            best[i][j] = 1, 
            f[i][j] = infll;
    }
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        pre[i] = a[i] + pre[i - 1];
    }
    for (int i = 1; i <= n; i++)
        f[i][i] = 0, best[i][i] = i;
    for (int len = 2; len <= n; len++){
        for (int i = 1; i <= n - len + 1; i++){
            int j = i + len - 1;
            f[i][j] = infll;
            int ptr = best[i][j - 1];
            int val = pre[j] - pre[i - 1];
            int l = best[i][j - 1], r = best[i + 1][j], md;
            for (int k = l; k <= r; k++){
                if ( f[i][k] + f[k + 1][j] + val < f[i][j] ){
                    f[i][j] = f[i][k] + f[k + 1][j] + val;
                    best[i][j] = k;
                }
            }
        }
    }
    cout << f[1][n];
}


