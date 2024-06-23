#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 2e5 + 5;

const int S = sqrt( N ) + 5;

const int M = 1e6 + 5;

int n, q, a[N];

int cnt[M];
long long res[N];

long long ans = 0;

vector< pair< ii, int > > qu;

bool cmp( pair< ii, int > x, pair< ii, int > y ){
    if ( x.fi.fi / S != y.fi.fi / S ) return x.fi.fi < y.fi.fi;
    return x.fi.se < y.fi.se;
}

int moveLeft( int L, int l ){
    while ( L < l ){
        int x = a[L];
        ans -= 1ll * cnt[x] * 1ll * cnt[x] * x;
        cnt[x]--;
        ans += 1ll * cnt[x] * 1ll * cnt[x] * x;
        L++;
    }
    while ( L > l ){
        L--;
        int x = a[L];
        ans -= 1ll * cnt[x] * 1ll * cnt[x] * x;
        cnt[x]++;
        ans += 1ll * cnt[x] * 1ll * cnt[x] * x;
    }
    return L;
}

int moveRight( int R, int r ){
    while ( R < r ){
        R++;
        int x = a[R];
        ans -= 1ll * cnt[x] * 1ll * cnt[x] * x;
        cnt[x]++;
        ans += 1ll * cnt[x] * 1ll * cnt[x] * x;
    }
    while ( R > r ){
        int x = a[R];
        ans -= 1ll * cnt[x] * 1ll * cnt[x] * x;
        cnt[x]--;
        ans += 1ll * cnt[x] * 1ll * cnt[x] * x;
        R--;
    }
    return R;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= q; i++){
        int l, r;
        cin >> l >> r;
        qu.pb( mp( mp( l, r ), i ) );
    }
    sort( qu.begin(), qu.end(), cmp );
    for (int i = qu[0].fi.fi; i <= qu[0].fi.se; i++){
        int x = a[i];
        ans -= 1ll * cnt[x] * 1ll * cnt[x] * x;
        cnt[x]++;
        ans += 1ll * cnt[x] * 1ll * cnt[x] * x;
    }
    res[qu[0].se] = ans;
    int L = qu[0].fi.fi, R = qu[0].fi.se;
    for (int i = 1; i < (int)( qu.size() ); i++){
        int l = qu[i].fi.fi, r = qu[i].fi.se;
        L = moveLeft( L, l );
        R = moveRight( R, r );
        res[ qu[i].se ] = ans;
    }
    for (int i = 1; i <= (int)( qu.size() ); i++)
        cout << res[i] << "\n";
}
