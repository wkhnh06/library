#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define int long long
typedef pair< long long, long long > ii;

const int N = 2e5 + 5;
const long long inf = 1e18;

struct ConvexHull {
    vector < ii > pts;
    int pter = 0;
    ConvexHull(){
        pter = 0; pts.clear();
    }
    bool check(ii p3, ii p2, ii p1){
        long double cmp1 = (long double)(p3.se - p1.se) / (long double)(p1.fi - p3.fi);
        long double cmp2 = (long double)(p3.se - p2.se) / (long double)(p2.fi - p3.fi);
        return (cmp1 <= cmp2);
    }
    void add_line(long long a, long long b){
        pts.pb( mp( a, b ) );
        while ((int)(pts.size()) >= 3 && check(pts[(int)(pts.size()) - 3], pts[(int)(pts.size()) - 2], pts[(int)(pts.size()) - 1]) ){
            ii tmp = pts[(int)(pts.size()) - 1];
            pts.pop_back(); pts.pop_back();
            pts.pb(tmp);
        }
    }
    long long get_ans(long long x){
        if ((int)(pts.size()) == 0) return inf;
        int l = 0, r = (int)(pts.size()) - 1, md1, md2;
        while (r - l > 2){
            md1 = l + (r - l) / 3, md2 = r - (r - l) / 3;
            if (pts[md1].fi * x + pts[md1].se < pts[md2].fi * x + pts[md2].se)
                r = md2;
            else if (pts[md1].fi * x + pts[md1].se > pts[md2].fi * x + pts[md2].se)
                l = md1;
            else
                l = md1, r = md2;
        }
        pter = min(pter, (int)(pts.size()) - 1);
        while (pter + 1 < (int)(pts.size()) && pts[pter].fi * x + pts[pter].se > pts[pter + 1].fi * x + pts[pter + 1].se)
            pter++;
        int mn = inf;
        for (int i = l; i <= r; i++)
            mn = min(mn, pts[i].fi * x + pts[i].se);
        return mn;
        return pts[pter].fi * x + pts[pter].se;
    }
}cv[N];

long long dp[N], ans = inf;

int n, m, flightA[N], flightB[N];

vector< pair < ii, int > > times;

signed main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int s, e;
        cin >> flightA[i] >> flightB[i] >> s >> e;
        times.pb( mp( mp( s, 1 ), i ) );
        times.pb( mp( mp( e, -1 ), i ) );
    }
    for (int i = 1; i <= m; i++)
        dp[i] = inf;
    cv[1].add_line(0, 0);
    sort(times.begin(), times.end());
    for (int i = 0; i < (int)(times.size()); i++){
        int a = flightA[times[i].se], b = flightB[times[i].se], t = times[i].fi.fi;
        if (times[i].fi.se == 1)
            dp[ times[i].se ] = min(dp[ times[i].se ], cv[a].get_ans(2ll * t) + 1ll * t * t);
        else {
            if (dp[ times[i].se ] == inf) continue;
            cv[b].add_line(-t, dp[ times[i].se ] + 1ll * t * t);
        }
        if (a == n || b == n)
            ans = min(ans, dp[ times[i].se ]);
    }
    cout << ans;
}

