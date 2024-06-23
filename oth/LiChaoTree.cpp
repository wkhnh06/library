#include<bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define sz(x) ( (int)(x).size() )
#define fi first
#define se second
using LL = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count() );

int n, m;

struct Line {
    int a;
    LL b;
    Line(int _a = 0, LL _b = 0) : a(_a), b(_b){}
    LL y(int x){ return (LL)a * x + b; }
};

struct LiChaoTree {
    vector<Line> line;
    LiChaoTree(int nNode){ line.assign(nNode, Line() ); }

    void add(Line val, int l, int r, int i = 1, int Left = 0, int Right = n - 1){
        if (r < Left || Right < l) return ;
        int Mid = (Left + Right) >> 1;
        if (l <= Left && Right <= r){
            bool cmpLeft = line[i].y(Left) < val.y(Left),
                 cmpMid = line[i].y(Mid) < val.y(Mid);
            if (cmpMid) swap(line[i], val);
            if (Left == Right) return ;
            if (cmpLeft != cmpMid) add(val, l, r, i << 1, Left, Mid);
            else add(val, l, r, i << 1 | 1, Mid + 1, Right);
        }
        else {
            add(val, l, r, i << 1, Left, Mid);
            add(val, l, r, i << 1 | 1, Mid + 1, Right);
        }
    }

    LL getMx(int x, int i = 1, int Left = 0, int Right = n - 1){
        int Mid = (Left + Right) >> 1;
        if (Left == Right) return line[i].y(x);
        if (x <= Mid) return max(line[i].y(x), getMx(x, i << 1, Left, Mid) );
        else return max(line[i].y(x), getMx(x, i << 1 | 1, Mid + 1, Right) );
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m;

    LiChaoTree lct( (n + 5) << 2);
    while (m--){
        int s, e, v, d; cin >> s >> e >> v >> d; --s; --e;
        lct.add(Line(d, -(LL)s * d + v), s, e);
    }

    for (int i = 0; i < n; ++i) cout << lct.getMx(i) << '\n';

    return 0;
}

