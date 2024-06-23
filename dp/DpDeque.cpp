#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

const int N = 500005;

deque<int> dq[2];

int n, k, dp[N], c[2][N];

string s, t;

const int inf = 1e8;

int main(){
    cin.tie(0), ios::sync_with_stdio(0);
    cin >> n >> k;
    cin >> s >> t;
    s = "+" + s;
    t = "+" + t;
    for (int i = 1; i <= n; i++){
        if (t[i] == 'W' && t[i] != t[i - 1])
            c[0][i] = 1;
        if (t[i] == 'B' && t[i] != t[i - 1])
            c[1][i] = 1;
        for (int j = 0; j <= 1; j++)
            c[j][i] += c[j][i - 1];
    }
    if (s[1] != t[1]){
        int id;
            if (t[1] == 'B')
                id = 0;
            else
                id = 1;
            dq[id].push_front(0);
    }
    for (int i = 1; i <= n; i++){
        dp[i] = inf;
        if (s[i] == t[i])
            dp[i] = dp[i - 1];
        for (int j = 0; j <= 1; j++){
            if (!dq[j].empty())
                dp[i] = min(dp[i], 1 + dp[dq[j].back()] - c[j][dq[j].back()] + c[j][i]);
            while (!dq[j].empty() && dq[j].back() < i - k + 1) dq[j].pop_back();
        }
        if (s[i + 1] != t[i + 1]){
            int id;
            if (t[i + 1] == 'B')
                id = 0;
            else
                id = 1;
            while (!dq[id].empty() && dp[dq[id].front()] - c[id][dq[id].front()] >= dp[i] - c[id][i])
                dq[id].pop_front();
            dq[id].push_front(i);
        }
    }
    cout << dp[n];
}
