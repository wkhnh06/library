#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int mod = 1e9 + 7;

const int N = 55;

int n, k, f[N];

int add( int x, int y ){
    return ( 1ll * x + 1ll * y ) % mod;
}

int mul( int x, int y ){
    return ( 1ll * x * 1ll * y ) % mod;
}

int del( int x, int y ){
    return ( ( 1ll * x - 1ll * y ) % mod + mod ) % mod;
}

int BinPow( int x, int y ){
    if ( y == 0 )
        return 1;
    else if ( y == 1 )
        return x;
    else {
        int Sum = BinPow( x, y / 2 );
        Sum = mul( Sum, Sum );
        if ( y % 2 )
            Sum = mul( Sum, x );
        return Sum;
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    while ( cin >> n >> k ){
        f[0] = 0;
        for (int i = 1; i <= k + 1; i++)
            f[i] = add( f[ i - 1 ], BinPow( i, k ) );
        int ans = 0;
        for (int i = 0; i <= k + 1; i++){
            int A = 1, B = 1;
            for (int j = 0; j <= k + 1; j++){
                if ( i == j ) continue;
                A = mul( A, del( n, j ) );
                B = mul( B, del( i, j ) );
            }
            A = mul( A, BinPow( B, mod - 2 ) );
            ans = add( ans, mul( A, f[i] ) );
        }
        cout << ans << "\n";
    }
}

