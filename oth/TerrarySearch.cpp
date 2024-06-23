#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int inf = 1e9;

const int N = 2e5 + 5;

int n;

double a[N];

double sum[N];

double check( double x ){
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + ( a[i] - x );
    double mn = 0, mx = 0, ans = 0;
    for (int i = 1; i <= n; i++){
        ans = max( ans, abs( sum[i] - mn ) );
        ans = max( ans, abs( sum[i] - mx ) );
        mn = min( mn, sum[i] );
        mx = max( mx, sum[i] );
    }
    return ans;
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    double mn = inf, mx = -inf;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        mn = min( mn, a[i] );
        mx = max( mx, a[i] );
    }
    double l = mn, r = mx, md1, md2;
    for (int i = 1; i <= 200; i++){
        md1 = l + ( r - l ) / 3;
        md2 = r - ( r - l ) / 3;
        double val1 = check( md1 ), val2 = check( md2 );
        if ( val1 < val2 )
            r = md2;
        else if ( val1 > val2 )
            l = md1;
        else
            l = md1, r = md2;
    }
    cout << setprecision(10) << fixed << check(l);
}


