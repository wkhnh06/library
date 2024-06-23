#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 2005;

int ccw( ii A, ii B, ii P ){
    long long ax = B.fi - A.fi;
    long long by = B.se - P.se;
    long long ay = B.se - A.se;
    long long bx = B.fi - P.fi;
    long long val = ax * by - ay * bx;
    if ( val < 0 )
        return -1;
    else if ( val == 0 )
        return 0;
    else
        return 1;
}

bool compare( ii A ){
    if ( A.se > 0 ) return 1;
    else if ( A.se == 0 && A.fi > 0 ) return 1;
    return 0;
}

bool cmp( ii A, ii B ){
    if ( compare( A ) != compare( B ) ) return compare( A ) > compare( B );
    return ccw( mp( 0, 0 ), A, B ) > 0;
}

int n;
ii pts[N];

long long res = 0, c[N];

vector< ii > S;

void solve( int id ){
    S.clear();
    for (int i = 1; i <= n; i++){
        if ( i == id ) continue;
        S.pb( mp( pts[i].fi - pts[id].fi, pts[i].se - pts[id].se ) );
    }
    sort( S.begin(), S.end(), cmp );
    int pter = 0, Sum = 0;
    for (int i = 0; i < n - 1; i++){
        Sum--;
        if ( i == pter ){ Sum++; pter = ( pter + 1 ) % ( n - 1 ); }
        while ( ccw( mp( 0, 0 ), S[i], S[pter] ) > 0 ){
            Sum++;
            pter = ( pter + 1 ) % ( n - 1 );
        }
        res += c[Sum] * c[( n - 2 - Sum )];
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= N - 5; i++)
        c[i] = ( 1ll * i * 1ll * ( i - 1 ) ) / 2ll;
    for (int i = 1; i <= n; i++)
        cin >> pts[i].fi >> pts[i].se;
    for (int i = 1; i <= n; i++)
        solve( i );
    cout << res / 2;
}
