//https://en.wikipedia.org/wiki/Lucas%27s_theorem
#include <bits/stdc++.h>

using namespace std;

const int mod = 100003;

int test;
#define fi first
#define se second
#define pb push_back

int add(int x, int y){
    return (1ll * x + 1ll * y) % mod;
}

int mul(int x, int y){
    return (1ll * x * 1ll * y) % mod;
}

int binpow( int x, int y ){
    if ( y == 0 )
        return 1;
    else if ( y == 1 )
        return x;
    else {
        int sum = binpow( x, y / 2 );
        sum = mul( sum, sum );
        if ( y % 2 )
            sum = mul( sum, x );
        return sum;
    }
}

const int N = 1e5 + 3;

int pre[N], suf[N];

int C(int n, int k){
    if ( n < k ) 
        return 0;
    return mul( pre[n], mul( suf[k], suf[ n - k ] ) );
}

vector< int > v1, v2;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> test;
    pre[0] = suf[0] = 1;
    for (int i = 1; i < N; i++)
        pre[i] = mul( pre[i - 1], i );
    suf[ N - 1 ] = binpow( pre[ N - 1 ], mod - 2 );
    for (int i = N - 2; i >= 1; i--)
        suf[i] = mul( suf[i + 1], i + 1 );
    while ( test-- ){
        long long n, m;
        cin >> n >> m;
        v1.clear(), v2.clear();
        long long tmp = m;
        while ( tmp != 0 ){
            long long rem = tmp % mod;
            v1.pb( rem );
            tmp /= mod;
        }
        tmp = n - m + 1;
        while ( tmp != 0 ){
            long long rem = tmp % mod;
            v2.pb( rem );
            tmp /= mod;
        }
        while ( (int)( v1.size() ) < (int)( v2.size() ) )
            v1.pb(0);
        while ( (int)( v2.size() ) < (int)( v1.size() ) )
            v2.pb(0);
        int sum = 1;
        for (int i = 0; i < (int)( v1.size() ); i++){
            sum = mul( sum, C( v2[i], v1[i] ) );
        }
        cout << sum << "\n";
    }
}

