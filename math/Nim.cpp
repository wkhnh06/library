#include<bits/stdc++.h>

using namespace std;

long long t,n,s[105],sum=0;

int main(){
    cin.tie(0),cout.tie(0),ios::sync_with_stdio(0);
    cin>>t;
    while (t--){
        sum=0;
        cin>>n;
        for (int i=1;i<=n;i++){
            cin>>s[i];
            sum=(sum^s[i]);
        }
        if (sum>0)
            cout<<"First\n";
        else
            cout<<"Second\n";
    }
}

