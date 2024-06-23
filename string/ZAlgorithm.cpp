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

int z[2 * N], l, r, n, m;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> a >> b;
    n = a.length(); m = b.length();
    a = b + a;
    a = "+" + a;
    z[1] = n + m;
    l = 1, r = 1;
    for (int i = 2; i <= m + n; i++){
        if (i > r){
            l = r = i;
            while (r <= m + n && a[r] == a[r - l + 1])
                r++;
            r--;
            z[i] = r - l + 1;
        }
        else {
            int k = i - l + 1;
            if (z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while (r <= m + n && a[r] == a[r - l + 1])
                    r++;
                r--;
                z[i] = r - l + 1;
            }
        }
        if (i > m && z[i] >= m)
            cout << i - m << " ";
    }
}


