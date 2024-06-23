#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

#define x1 Send
#define x2 Bobs
#define y1 To
#define y2 Alice

const int N = 1e3 + 5;
const int M = 3e5 + 5;

int n, a[N][N], pSet[N * N], m, H[N][N], Ans[ M ];

bool dead[N][N];

int getSum( int x1, int y1, int x2, int y2 ){
    return a[x2][y2] - a[x2][y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][y1 - 1];
}

bool check( int x, int y ){
    return (x >= 1 && x <= n && y >= 1 && y <= n && !dead[x][y]);
}

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

vector< pair< int, ii > > nodes;

int id( int x, int y ){
    return (x - 1) * n + y;
}

void reset(){
    for (int i = 1; i <= n * n; i++)
        pSet[i] = i;
}

int findSet( int u ){
    if ( u == pSet[u] ) return u;
    else return pSet[u] = findSet( pSet[u] );
}

void unionSet( int u, int v ){
    u = findSet( u ); v = findSet( v );
    if ( u == v ) return ;
    pSet[u] = v;
}

pair< ii, ii > qu[M];

pair< ii, ii > Para[M];

bool Ok[M];

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    reset();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            char c;
            cin >> c;
            a[i][j] = ( c == '#' );
            a[i][j] += a[i][j - 1];
            a[i][j] += a[i - 1][j];
            a[i][j] -= a[i - 1][j - 1];
            dead[i][j] = ( c == '#' );
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            int l = 1, r = min( min( i - 1, j - 1 ), min( n - i, n - j ) ) + 1, md;
            while ( l < r ){
                md = (l + r + 1) >> 1;
                if ( getSum( i - md + 1, j - md + 1, i + md - 1, j + md - 1 ) == 0 )
                    l = md;
                else
                    r = md - 1;
            }
            if ( getSum( i - l + 1, j - l + 1, i + l - 1, j + l - 1 ) ) continue;
            H[i][j] = 2 * l - 1;
            nodes.pb( mp( 2 * l - 1, mp( i, j ) ) );
        }
    }
    sort( nodes.begin(), nodes.end() );
    reverse( nodes.begin(), nodes.end() );
    cin >> m;
    for (int i = 1; i <= m; i++){
        cin >> qu[i].fi.fi >> qu[i].fi.se >> qu[i].se.fi >> qu[i].se.se;
        Para[i].se.fi = 0, Para[i].se.se = n, Para[i].fi.fi = (n + 1) >> 1, Para[i].fi.se = i;
    }
    int lim = (int)( nodes.size() );
    for (int T = 1; T <= 10; T++){
        sort( Para + 1, Para + 1 + m );
        reset();
        int ptr = 0;
        for (int i = m; i >= 1; i--){
            while ( ptr < lim && nodes[ptr].fi >= Para[i].fi.fi ){
                int x = nodes[ptr].se.fi, y = nodes[ptr].se.se;
                for (int j = 0; j < 4; j++){
                    if ( !check( x + dx[j], y + dy[j] ) ) continue;
                    if ( H[ x + dx[j] ][ y + dy[j] ] >= Para[i].fi.fi )
                        unionSet( id( x, y ), id( x + dx[j], y + dy[j] ) );
                }
                ptr++;
            }
            int ide = Para[i].fi.se;
            Ok[ ide ] = ( findSet( id( qu[ide].fi.fi, qu[ide].fi.se ) ) == findSet( id( qu[ide].se.fi, qu[ide].se.se ) ) );
        }
        for (int i = 1; i <= m; i++){
            if ( Ok[ Para[i].fi.se ] )
                Para[i].se.fi = Para[i].fi.fi;
            else
                Para[i].se.se = Para[i].fi.fi - 1;
            Para[i].fi.fi = ( Para[i].se.fi + Para[i].se.se + 1 ) / 2;
            Ok[ Para[i].fi.se ] = 0;
        }
    }
    for (int i = 1; i <= m; i++)
        Ans[ Para[i].fi.se ] = Para[i].se.fi;
    for (int i = 1; i <= m; i++)
        cout << Ans[i] << "\n";
}
