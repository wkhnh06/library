#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;
const int inf = 1e9;

const int N = 1e5 + 5;

int n, K, a[N], L, R;

long long ans = 0, cnt[N], dp[25][N];

long long query( int l, int r ){
    while ( L < l ){
        int x = a[L];
        ans -= cnt[ x ] * (cnt[x] - 1) / 2;
        cnt[x]--;
        ans += cnt[ x ] * (cnt[x] - 1) / 2;
        L++;
    }
    while ( L > l ){
        L--;
        int x = a[L];
        ans -= cnt[ x ] * (cnt[x] - 1) / 2;
        cnt[x]++;
        ans += cnt[ x ] * (cnt[x] - 1) / 2;
    }
    while ( R < r ){
        R++;
        int x = a[R];
        ans -= cnt[ x ] * (cnt[x] - 1) / 2;
        cnt[x]++;
        ans += cnt[ x ] * (cnt[x] - 1) / 2;
    }
    while ( R > r ){
        int x = a[R];
        ans -= cnt[ x ] * (cnt[x] - 1) / 2;
        cnt[x]--;
        ans += cnt[ x ] * (cnt[x] - 1) / 2;
        R--;
    }
    return ans;
}

queue< pair< ii, ii > > qu;

void solve( int lvl ){
    qu.push( mp( mp( lvl, n ), mp( lvl, n ) ) );
    while ( !qu.empty() ){
        pair< ii, ii > frt = qu.front();
        qu.pop();
        int md, l = frt.fi.fi, r = frt.fi.se, bl = frt.se.fi, br = frt.se.se;
        md = ( l + r ) / 2;
        long long best = -1;
        dp[lvl][md] = 1ll * inf * 1ll * inf;
        for (int i = bl; i <= min( md, br ); i++){
            if ( dp[ lvl - 1 ][i - 1] + query( i, md ) < dp[lvl][md] ){
                dp[lvl][md] = dp[ lvl - 1 ][i - 1] + query( i, md );
                best = i;
            }
        }
        if ( l <= md - 1 )
            qu.push( mp( mp( l, md - 1 ), mp( bl, best ) ) );
        if ( md + 1 <= r )
            qu.push( mp( mp( md + 1, r ), mp( best, br ) ) );
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> K;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    L = 1, R = 0;
    for (int i = 1; i <= n; i++)
        dp[1][i] = query( 1, i );
    for (int i = 2; i <= K; i++){
        solve( i );
    }
    cout << dp[K][n];
}

