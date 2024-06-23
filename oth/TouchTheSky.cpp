#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

vector< pair< long long, ii > > edge;

int n;

priority_queue< int > pq;

long long sum = 0;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++){
        long long l, d;
        cin >> l >> d;
        edge.pb( mp( l + d, mp( l, d ) ) );
    }
    sort( edge.begin(), edge.end() );
    for (int i = 0; i < n; i++){
        sum += edge[i].se.se;
        pq.push( edge[i].se.se );
        if ( sum > edge[i].fi ){
            while ( !pq.empty() && sum > edge[i].fi ){
                long long u = pq.top();
                pq.pop();
                sum -= u;
            }
        }
    }
    cout << pq.size();
}
