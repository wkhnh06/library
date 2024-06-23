//https://vn.spoj.com/problems/SUBSTR/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e6 + 5;
const int mod = 1e9 + 7;
const int base = 97;

string a, b;

int add(int x, int y){
    return (1ll * x + 1ll * y) % mod;
}

int mul(int x, int y){
    return (1ll * x * 1ll * y) % mod;
}

int del(int x, int y){
    return ( (1ll * x - 1ll * y) % mod + mod ) % mod;
}

int hs[N], pw[N], n, m, hsB;

int getHs(int l, int r){
    return del( hs[r], mul( hs[l - 1], pw[r - l + 1] ) );
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> a >> b;
    n = a.length(); m = b.length();
    a = "+" + a;
    b = "+" + b;
    pw[0] = 1;
    for (int i = 1; i < N; i++)
        pw[i] = mul( pw[i - 1], base );
    for (int i = 1; i <= m; i++)
        hsB = add( mul( hsB, base ), b[i] - 'a' + 1 );
    for (int i = 1; i <= n; i++)
        hs[i] = add( mul( hs[i - 1], base ), a[i] - 'a' +  1 );
    for (int i = 1; i <= n - m + 1; i++){
        if ( getHs( i, i + m - 1 ) == hsB)
            cout << i << " ";
    }
}

