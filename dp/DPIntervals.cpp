#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 205;

const int mod = 1e9 + 7;

int dp[2][N][1005], a[N], n, K;

int addu( int x, int y ){
    return ( 1ll * x + 1ll * y ) % mod;
}

int deld( int x, int y ){
    return addu( ( 1ll * x - 1ll * y ) % mod, mod );
}

int mul( int x, int y ){
    return ( 1ll * x * 1ll * y ) % mod;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> K;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort( a + 1, a + 1 + n );
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < i; j++){
            for (int k = 0; k <= K; k++){
                int amount = k + ( a[i] - a[i - 1] ) * j;
                if ( !dp[0][j][k] ) continue;
                if ( amount > K ) continue;
                dp[1][j + 1][amount] = addu( dp[1][j + 1][amount], dp[0][j][k] );//open up new ones
                dp[1][j][ amount ] = addu( dp[1][j][amount], dp[0][j][k] );//single person
                dp[1][j][ amount ] = addu( dp[1][j][amount], mul( dp[0][j][k], j) );
                if (j)
                    dp[1][j - 1][ amount ] = addu( dp[1][j - 1][ amount ], mul( dp[0][j][k], j ) );
            }
        }
        for (int j = 0; j <= i; j++){
            for (int k = 0; k <= K; k++){
                dp[0][j][k] = dp[1][j][k];
                dp[1][j][k] = 0;
            }
        }
    }
    int ans = 0;
    for (int k = 0; k <= K; k++)
        ans = addu( ans, dp[0][0][k] );
    cout << ans;
}
