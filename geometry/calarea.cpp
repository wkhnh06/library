//https://www.spoj.com/problems/CALCAREA/en/
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair<int, int> ii;

const int N = 1e4 + 5;

int n;

pair<long long, long long> p[N];

long long sum;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i].fi >> p[i].se;
    for (int i = 0; i < n; i++)
        sum += (p[(i + 1) % n].fi - p[i].fi) * (p[(i + 1) % n].se + p[i].se);
    sum = abs(sum);
    if (sum % 2 == 0)
        cout << sum / 2 << "\n";
    else
        cout << sum / 2 + 1 << "\n";
}
