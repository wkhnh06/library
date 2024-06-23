#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ll long long
typedef pair<int, int> ii;

const int N = 5e3 + 5;
const ll inf = 2ll * 1e9 * 1e9;
ll dp[N][N];

int n, s, e, x[N], a[N], b[N], c[N], d[N];

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n >> s >> e;
    for (int i = 1; i <= n; i++)
        cin >> x[i];
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    //a thời gian hạ cánh nếu đi từ i < j
    //d thời gian cất cánh nếu đi từ i < j
    //b thời gian hạ cánh nếu đi từ i > j
    //c thời gian cất cánh nếu đi từ i > j
    if (s == 1)
        dp[1][1] = d[1] - x[1];
    else if (e == 1)
        dp[1][1] = b[1] - x[1];
    else
        dp[1][1] = d[1] + b[1] - 2 * x[1];
    cerr << 7;
    for (int i = 2; i <= n; i++){
        for (int j = 1; j <= i; j++){
            dp[i][j] = inf;
            //if (i > s && i > e && j == 1) continue;
            //ghép vào bên trái một component
            if (i != e && i - 1 >= j){
                if (i - 1 >= e && i - 1 >= s && j == 1){}
                else {
                    if (j == 1 && i - 1 >= s){}
                    else
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + c[i] + x[i] + (i != s) * (b[i] - x[i]));
                }
            }
            if (i != s && i - 1 >= j){
                if (i - 1 >= e && i - 1 >= s && j == 1){}
                else {
                    if (j == 1 && i - 1 >= e){}
                    else
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i] + x[i] + (i != e) * (d[i] - x[i]));
                }
            }
            if (i != s && i != e && j + 1 <= i - 1)
                dp[i][j] = min(dp[i][j], dp[i - 1][j + 1] + (i != s) * (a[i] + x[i]) + (i != e) * (c[i] + x[i]));
            if (j > 1){
                if (i - 1 >= e && i - 1 >= s && j - 1 == 1){}
                else
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (i != s) * (b[i] - x[i]) + (i != e) * (d[i] - x[i]));
            }
        }
    }
    cout << dp[n][1];
}
/*7 4 3
8 11 12 16 17 18 20
17 16 20 2 20 5 13
17 8 8 16 12 15 13
12 4 16 4 15 7 6
8 14 2 11 17 12 8
*/
