#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

ii exEuclid( long long A, long long B ){
    if ( B == 0 ) 
        return mp( 1, 0 );
    else {
        ii tmp = exEuclid( B, A % B );
        return { tmp.se, tmp.fi - (A/B) * tmp.se };
    }
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    long long A, B;
    cin >> A >> B;
    ii tmp = exEuclid( A, B );
    cout << tmp.fi << " " << tmp.se << "\n";
}
