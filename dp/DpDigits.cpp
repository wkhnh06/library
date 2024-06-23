#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;
const int inf = 1e9;

int q;

long long n, K, dp[2][22][200][3];

string Up = "", UpK = "";

int sumDig( long long  x ){
    int total = 0;
    while ( x != 0 ){
        total += x % 10;
        x /= 10;
    }
    return total;
}

void sub1( int type ){
    vector< pair< int, string > > nums;
    for (int i = 1; i <= n; i++){
        int x = i, total = 0;
        string s = "";
        while ( x != 0 ){
            total += x % 10;
            s += (x % 10 + '0');
            x /= 10;
        }
        reverse( s.begin(), s.end() );
        nums.pb( mp( total, s ) );
    }
    sort( nums.begin(), nums.end() );
    if ( type == 1 )
        cout << nums[ K - 1 ].se << "\n";
    else {
        string t = "";
        while ( K != 0 ){
            t += (K % 10 + '0');
            K /= 10;
        }
        reverse( t.begin(), t.end() );
        for (int i = 0; i < (int)( nums.size() ); i++){
            if ( nums[i].se == t ){
                cout << i + 1 << "\n";
                break;
            }
        }
    }
}

string trans( long long num ){
    string s = "";
    while ( num > 0 ){
        s += (char)( num % 10 + '0' );
        num /= 10;
    }
    reverse( s.begin(), s.end() );
    s = "0" + s;
    return s;
}

long long f(int type, int pos, int lim, int cursum, int ok, int reqsum){
    long long ans = dp[ type ][ pos ][ cursum ][ ok ];
    if ( ans != -1 ) return ans;
    ans = 0;
    if ( pos < lim ){
        if ( type == 1 ){
            if ( cursum == reqsum )
                ans++;
        }
        else if ( cursum > 0 )
            ans++;
    }
    if ( pos == lim ){
        if ( ok == 2 ) return 0;
        if ( type == 1 )
            return ( cursum == reqsum );
        else
            return 1;
    }
    int l = ( pos == 1 ), r = 9;
    for (int i = l; i <= r; i++){
        int ncursum = cursum + i, nok = ok;
        if ( ok == 1 && i > Up[pos] - '0' ) nok = 2;
        if ( ok == 1 && i == Up[pos] - '0' ) nok = 1;
        if ( ok == 1 && i < Up[pos] - '0' ) nok = 0;
        if ( type == 0 ){
            if ( ncursum >= reqsum ) break;
            ans += f( type, pos + 1, lim, ncursum, nok, reqsum );
        }
        else {
            if ( ncursum > reqsum ) break;
            ans += f( type, pos + 1, lim, ncursum, nok, reqsum );
        }
    }
    dp[ type ][ pos ][ cursum ][ ok ] = ans;
    return ans;
}

void reset(){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 22; j++){
            for (int o = 0; o < 200; o++){
                for (int l = 0; l < 3; l++)
                    dp[i][j][o][l] = -1;
            }
        }
    }
}

void sub2(){
    reset();
    long long Sum = sumDig( K ); //sum digits of k
    Up = trans( n );
    //cout << Up.size() << "\n";
    long long Res = f( 0, 1, Up.size(), 0, 1, Sum );
    int curDig = 0, curOk = 1;
    UpK = trans( K );
    for (int i = 0; i < (int)(UpK.size()) - 1; i++){ //Numbers that sumDigits = K but smaller lexi
        curDig += (UpK[i] - '0');
        int ncurOk = curOk;
        if ( curOk == 1 && Up[i] > UpK[i] ) ncurOk = 0;
        if ( curOk == 1 && Up[i] < UpK[i] ) ncurOk = 2;
        if ( curDig == Sum ) Res++;
        for (int j = (i == 0); j < UpK[i + 1] - '0'; j++){
            reset();
            curDig += j;
            int tmpcurOk = ncurOk;
            if ( ncurOk == 1 && Up[i + 1] - '0' > j ) tmpcurOk = 0;
            if ( ncurOk == 1 && Up[i + 1] - '0' < j ) tmpcurOk = 2;
            Res += f( 1, i + 2, Up.size(), curDig, tmpcurOk, Sum );
            curDig -= j;
        }
        curOk = ncurOk;
    }
    cout << Res + 1 << "\n";
}

void sub3(){
    Up = trans( n );
    long long Sum = 0;
    int lim = (int)( Up.size() );
    for (int i = 1; i < 200; i++){
        reset();
        long long Num = f( 1, 1, lim, 0, 1, i );
        if ( Num >= K ){
            Sum = i;
            break;
        }
        else
            K -= Num;
    }
    //cout << K << " " << Sum << "\n";
    int pos = 1, curOk = 1, curSum = 0;
    while ( 1 ){
        if ( curSum == Sum && K == 1 ) break;
        else if ( curSum == Sum && K > 1 ){
            cout << "0";
            K--;
        }
        else {//type, pos, limit, curDig, curOk, targetSum
            int l = (pos == 1), r = 9;
            for (int i = l; i <= r; i++){
                reset();
                int tmpOk = curOk;
                curSum += i;
                if ( curOk == 1 && i < (int)(Up[pos] - '0') )
                    tmpOk = 0;
                if ( curOk == 1 && i > (int)(Up[pos] - '0') )
                    tmpOk = 2;
                long long Num = f( 1, pos + 1, lim, curSum, tmpOk, Sum );
                //cout << Num << " " << curSum << " " << tmpOk << " " << Sum << "-------\n";
                if ( Num >= K ){
                    curOk = tmpOk;
                    cout << i;
                    pos++;
                    break;
                }
                else
                    K -= Num;
                curSum -= i;
            }
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> q;
    while (q--){
        int t;
        cin >> t >> n >> K;
        Up = "", UpK = "";
        if ( t == 0 )
            sub2();
        if ( t == 1 )
            sub3();
    }
}


