#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

string s, tmp;
const int N = 1e5 + 5;

int n, m, l, r, pa[N];

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++){
        tmp += '#';
        m++;
        tmp += s[i - 1];
        m++;
    }
    tmp += '#';
    m++;
    s = tmp;
    l = -1, r = -1;
    int ans = 0;
    for (int i = 0; i < m; i++){
        if (r < i){
            l = r = i;
            while (l >= 0 && r < m && s[l] == s[r])
                l--, r++;
            l++; r--;
            pa[i] = (r - l + 1);
        }
        else {
            int md = (l + r) / 2;
            int mirror = i - ( i - md ) * 2;
            if ( pa[ mirror ] / 2 + 1 < (r - i + 1) )
                pa[i] = pa[ mirror ];
            else {
                l = i - (r - i);
                while (l >= 0 && r < m && s[l] == s[r])
                    l--, r++;
                l++; r--;
                pa[i] = (r - l + 1);
            }
        }
        ans = max( ans, pa[i] / 2 );
    }
    cout << ans;
}

