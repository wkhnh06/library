//https://csacademy.com/contest/archive/task/superstition/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#pragma GCC optimize("O3")

typedef pair< int, int > ii;

const int N = 80 + 5;

const int M = 1e4 + 5;

const int mod = 1e9 + 7;

const long long mod2 = 1ll * mod * 1ll * mod;

int sz;

struct Matrix{
    int a[305][305];
    Matrix(){
        memset( a, 0, sizeof(a) );
    }
}Base, Tmp, C, res;

struct Matrix1xn{
    int a[305];
    Matrix1xn(){
        memset( a, 0, sizeof(a) );
    }
}State, D;

Matrix mulMatrix(Matrix A, Matrix B){
    for (int i = 0; i < sz; i++){
        for (int j = 0; j < sz; j++){
            long long sum = 0;
            for (int k = 0; k < sz; k++){
                sum += 1ll * A.a[i][k] * B.a[k][j];
                sum -= ( sum >= mod2 ? mod2 : 0 );
            }
            C.a[i][j] = sum % mod;
        }
    }
    return C;
}

Matrix1xn mulMatrix1xn(Matrix1xn A, Matrix B){
    for (int j = 0; j < sz; j++){
        long long sum = 0;
        for (int k = 0; k < sz; k++){
            sum += 1ll * A.a[k] * B.a[k][j];
            sum -= ( sum >= mod2 ? mod2 : 0 );
        }
        D.a[j] = sum % mod;
    }
    return D;
}

Matrix BinPow( Matrix x, int m ){
    if ( m == 1 )
        return x;
    else {
        Tmp = BinPow( x, m / 2 );
        Tmp = mulMatrix( Tmp, Tmp );
        if ( m % 2 ) Tmp = mulMatrix( Tmp, x );
        return Tmp;
    }
}

int Add(int x, int y){
    return ( 1ll * x + 1ll * y >= mod ? (1ll * x + 1ll * y) % mod : 1ll * x + 1ll * y );
}

int n, m, d, k, edge[N][N], dp[N][M];

void sub2(){
    int ans = 0;
    for (int u = 0; u < n; u++)
        dp[u][0] = 1;
    for (int t = 0; t <= k; t++){
        for (int u = 0; u < n; u++){
            if ( !dp[u][t] ) continue;
            for (int v = 0; v <=n; v++){
                if ( t + edge[u][v] <= k )
                    dp[v][ t + edge[u][v] ] = Add( dp[v][ t + edge[u][v] ], dp[u][t] );
            }
            if ( t > 0 && t % d == 0 )
                ans = Add( ans, dp[u][t] );
        }
    }
    cout << ans << "\n";
}

void sub6(){
    sz = n * 10;
    for (int u = 0; u < n; u++){
        for (int t = 1; t < 10; t++)
            Base.a[u * 10 + t][u * 10 + t - 1] = 1;
        for (int v = 0; v < n; v++){
            if ( edge[u][v] != mod )
                Base.a[ u * 10 ][ v * 10 + edge[u][v] - 1 ] = 1;
        }
        State.a[u * 10] = 1;
    }
    res = BinPow(Base, d);
    for (int i = 0; i < n; i++)
        res.a[i * 10][sz] = 1;
    res.a[sz][sz] = 1; sz++;
    res = BinPow(res,  k / d);
    State = mulMatrix1xn(State, res);
    int ans = mod - n;
    for (int i = 0; i <= n; i++)
        ans = Add( ans, State.a[i * 10] );
    cout << ans << "\n";
    exit(0);
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m >> d >> k;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            edge[i][j] = mod;
    }
    for (int i = 0; i < m; i++){
        int u, v, t;
        cin >> u >> v >> t;
        u--; v--;
        edge[u][v] = edge[v][u] = t;
    }
    if ( k <= 10000 )
        sub2();
    else
        sub6();
}
