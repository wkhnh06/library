#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

string s, t;

const int N = 1e6 + 5;

int n, m, nxt[N];

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> s >> t;
    n = (int)( s.length() );
    m = (int)( t.length() );
    nxt[0] = 0;
    for (int i = 1; i < m; i++){
        int tmp = nxt[ i - 1 ];
        while ( tmp > 0 && t[i] != t[ tmp ] )
            tmp = nxt[ tmp - 1 ];
        nxt[i] = tmp;
        if ( t[i] == t[ tmp ] )
            nxt[i]++;
    }
    int tmp = 0;
    for (int i = 0; i < n; i++){
        while ( tmp > 0 && s[i] != t[ tmp ])
            tmp = nxt[ tmp - 1 ];
        if ( s[i] == t[ tmp ] )
            tmp++;
        if ( tmp == m )
            cout << i - m + 2 << " ";
    }
}

