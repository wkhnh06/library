#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

const int N = 1e5 + 5;

int n, h[N];

stack< int > st;

long long mx = 0;

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    while ( cin >> n && n){
        mx = 0;
        for (int i = 1; i <= n; i++)
            cin >> h[i];
        while ( !st.empty() ) 
            st.pop();
        for (int i = 1; i <= n; i++){
            if (st.empty() || h[ st.top() ] < h[i])
                st.push(i);
            else {//h[st.top()] >= h[i]
                while ( !st.empty() && h[st.top()] >= h[i] ){
                    int x = h[ st.top() ];
                    st.pop();
                    int len = i - 1 - ( st.empty() ? 0 : (st.top()) );
                    mx = max( mx, 1ll * len * x );
                }
                st.push(i);
            }
        }
        while ( !st.empty() ){
            int x = h[ st.top() ];
            st.pop();
            int len = n - ( st.empty() ? 0 : (st.top()) );
            mx = max( mx, 1ll * len * x );
        }
        cout << mx << "\n";
    }
}

