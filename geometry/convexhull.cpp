//https://open.kattis.com/problems/convexhull
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

const int N = 1e4 + 5;

int n, m;

ii pts[N];

map< ii, bool > used;

vector< ii > up, down;

int ccw(ii A, ii B, ii P){
    int val = (B.fi - A.fi) * (B.se - P.se) - (B.se - A.se) * (B.fi - P.fi);
    if (val < 0)
        return -1;
    else if (val == 0)
        return 0;
    else
        return 1;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    while (cin >> n){
        if (!n) break;
        m = 0; used.clear(); down.clear(); up.clear();
        for (int i = 1; i <= n; i++){
            ii p;
            cin >> p.fi >> p.se;
            if (used.count(p) == 0){
                used[p] = 1;
                pts[++m] = p;
            }
        }
        n = m;
        sort(pts + 1, pts + 1 + n);
        if (n == 1){
            cout << 1 << "\n";
            cout << pts[1].fi << " " << pts[1].se << "\n";
            continue;
        }
        for (int i = 1; i <= n; i++){
            while (up.size() >= 2 && ccw(up[(int)(up.size()) - 2], up[(int)(up.size()) - 1], pts[i]) <= 0) up.pop_back();
            up.pb(pts[i]);
        }
        for (int i = n; i >= 1; i--){
            while (down.size() >= 2 && ccw(down[(int)(down.size()) - 2], down[(int)(down.size()) - 1], pts[i]) <= 0) down.pop_back();
            down.pb(pts[i]);
        }
        cout << (int)(up.size()) + (int)(down.size()) - 2 << "\n";
        for (int i = (int)(down.size()) - 1; i >= 0; i--)
            cout << down[i].fi << " " << down[i].se << "\n";
        for (int i = (int)(up.size()) - 2; i >= 1; i--)
            cout << up[i].fi << " " << up[i].se << "\n";
    }
}
