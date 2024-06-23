#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define x1 Send
#define y1 Bobs
#define x2 To
#define y2 Alice

typedef pair< int, int > ii;

const int N = 405;
const int inf = 1e9;

int n, m, q, rmq[2][10][10][N][N], mylog[N];

int get( int x1, int y1, int x2, int y2 ){
    int A = mylog[ x2 - x1 + 1 ], B = mylog[ y2 - y1 + 1 ];
    int mn = min( rmq[0][A][B][x1][y1], rmq[0][A][B][x1][ y2 - (1 << B) + 1 ] );
    mn = min( mn, rmq[0][A][B][x2 - (1 << A) + 1][y1] );
    mn = min( mn, rmq[0][A][B][x2 - (1 << A) + 1][y2 - (1 << B) + 1] );
    int mx = max( rmq[1][A][B][x1][y1], rmq[1][A][B][x1][ y2 - (1 << B) + 1 ] );
    mx = max( mx, rmq[1][A][B][x2 - (1 << A) + 1][y1] );
    mx = max( mx, rmq[1][A][B][x2 - (1 << A) + 1][y2 - (1 << B) + 1] );
    return ( mx - mn );
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    for (int i = 0; i < N; i++)
        mylog[i] = log2( i );
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int x;
            cin >> x;
            rmq[0][0][0][i][j] = rmq[1][0][0][i][j] = x;
        }
    }
    for (int i = 1; i <= n; i++){
        for (int k = 1; k < 10; k++){
            for (int j = 1; j <= m - ( 1 << ( k - 1 ) ); j++){
                int bit = j + ( 1 << ( k - 1 ) );
                rmq[0][0][k][i][j] = min( rmq[0][0][ k - 1 ][i][j], rmq[0][0][ k - 1 ][i][bit] );
                rmq[1][0][k][i][j] = max( rmq[1][0][ k - 1 ][i][j], rmq[1][0][ k - 1 ][i][bit] );
            }
        }
    }
    for (int bitX = 1; bitX < 10; bitX++){
        for (int i = 1; i <= n - ( 1 << ( bitX - 1 ) ); i++){
            int nxt = i + ( 1 << ( bitX - 1 ) );
            for (int bitY = 0; bitY < 10; bitY++){
                for (int j = 1; j <= m; j++){
                    rmq[0][bitX][bitY][i][j] = min( rmq[0][bitX - 1][bitY][i][j], rmq[0][bitX - 1][bitY][nxt][j] );
                    rmq[1][bitX][bitY][i][j] = max( rmq[1][bitX - 1][bitY][i][j], rmq[1][bitX - 1][bitY][nxt][j] );
                }
            }
        }
    }
    while (q--){
        int val;
        long long ans = 0;
        cin >> val;
        for (int i = 1; i <= n; i++){
            for (int j = i; j <= n; j++){
                int pter = 1;
                for (int k = 1; k <= m; k++){
                    while ( pter <= k && get( i, pter, j, k ) > val )
                        pter++;
                    ans += ( k - pter + 1 );
                }
            }
        }
        cout << ans << "\n";
    }
}
