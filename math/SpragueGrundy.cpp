#include<bits/stdc++.h>

using namespace std;
vector<int> div1[100005];
int g[100005],used[1000005];
#define N 100000
vector<int> ans;
int main(){
    cin.tie(0),cout.tie(0),ios::sync_with_stdio(0);
    g[1]=0;
    for (int i=1;i<=N;i++){
        for (int j=1;j<=(N/i);j++){
            div1[i*j].push_back(i);
        }
    }
    for (int i=2;i<=N;i++){
        for (int j=0;j<div1[i].size();j++){
            if (div1[i][j]!=i){
                long long t=i/div1[i][j];
                if (t%2!=0){
                    if (used[g[div1[i][j]]]==0){
                    used[g[div1[i][j]]]=1;
                    ans.push_back(g[div1[i][j]]);
                    }
                }
                else{
                    if (used[0]==0){
                    used[0]=1;
                    ans.push_back(0);
                    }
                }
            }
        }
        long long count1=0;
        sort(ans.begin(),ans.end());
        for (int j=0;j<ans.size();j++){
            if (ans[j]==count1)
                count1++;
            else
                break;
        }
        for (int j=0;j<ans.size();j++)
            used[ans[j]]=0;
        ans.clear();
        g[i]=count1;
    }
    int t;
    cin>>t;
    while (t--){
        int n,h;
        long long sum=0;
        cin>>n;
        while (n--){
            cin>>h;
            sum^=g[h];
        }
        if (sum==0)
            cout<<"2\n";
        else
            cout<<"1\n";
    }
}

