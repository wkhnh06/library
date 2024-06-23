string trans(long long num){
    int type = 0;
    string ans = "";
    if (num < 0) type = 1;
    num = abs( num );
    if ( num == 0 ) return "0";
    while ( num ){
        int x = num % 10;
        ans += (char)( x + '0' );
        num /= 10;
    }
    while ( (int)( ans.length() ) > 1 && ans[(int)( ans.length() ) - 1] == '0')
        ans.pop_back();
    reverse( ans.begin(), ans.end() );
    if ( type == 1 ) ans = "-" + ans;
    return ans;
}

string del(string a, string b);

string add(string a, string b){
    if ( a[0] == '-' && b[0] != '-' ){
        a.erase( a.begin() );
        return del( b, a );
    }
    if ( a[0] != '-' && b[0] == '-' ){
        b.erase( b.begin() );
        return del( a, b );
    }
    bool type = 0;
    if (a[0] == '-' && b[0] == '-'){
        type = 1;
        a.erase( a.begin() );
        b.erase( b.begin() );
    }
    while ( (int)( a.length() ) < (int)( b.length() ) )
        a = "0" + a;
    while ( (int)( b.length() ) < (int)( a.length() ) )
        b = "0" + b;
    string ans = "";
    int carry = 0;
    for (int i = (int)( a.length() ) - 1; i >= 0; i--){
        int sum = (int)( a[i] - '0' ) + (int)( b[i] - '0' ) + carry;
        if (sum >= 10){
            ans += (char)( sum - 10 + '0' );
            carry = 1;
        }
        else {
            ans += (char)( sum + '0' );
            carry = 0;
        }
    }
    if ( carry )
        ans += (char)( 1 + '0' );
    while (ans.length() > 1 && ans[(int)( ans.length() ) - 1] == '0')
        ans.pop_back();
    reverse( ans.begin(), ans.end() );
    if (type)
        ans = "-" + ans;
    return ans;
}

bool compare( string a, string b){
    if ( (int)( a.length() ) > (int)( b.length() ) )
        return 1;
    else if ( (int)( a.length() ) < (int)( b.length() ) )
        return 0;
    else {
        for (int i = 0; i < (int)( a.length() ); i++){
            if ( a[i] < b[i] )
                return 0;
            else if ( a[i] > b[i] )
                return 1;
        }
        return 1;
    }
}

string del( string a, string b ){
    if ( a[0] != '-' && b[0] == '-'){
        b.erase( b.begin() );
        return add( a, b );
    }
    else if ( a[0] == '-' && b[0] != '-' ){
        b = "-" + b;
        return add( a, b );
    }
    else if ( a[0] == '-' && b[0] == '-' ){
        b.erase( b.begin() );
        a.erase( a.begin() );
        swap( a, b );
    }
    int type = 0;
    if ( a == b ) return "0";
    if ( compare( a, b ) == 0 ){
        swap( a, b );
        type = 1;
    }
    while ( (int)( a.length() ) < (int)( b.length() ) ) a = "0" + a;
    while ( (int)( b.length() ) < (int)( a.length() ) ) b = "0" + b;
    int carry = 0;
    string ans = "";
    for (int i = (int)( a.length() ) - 1; i >= 0; i--){
        int sum = (int)( a[i] - '0' ) - (int)( b[i] - '0' ) - carry;
        if (sum < 0){
            sum += 10;
            ans += (char)( sum + '0' );
            carry = 1;
        }
        else {
            ans += (char)( sum + '0' );
            carry = 0;
        }
    }
    while ( (int)( ans.length() ) > 1 && ans[ (int)( ans.length() ) - 1 ] == '0') ans.pop_back();
    reverse( ans.begin(), ans.end() );
    if ( type == 1 )
        ans = "-" + ans;
    return ans;
}

string mul( string a, string b ){
    int type = 0;
    if ( a[0] == '-' && b[0] != '-' )
        type = 1;
    else if ( a[0] != '-' && b[0] == '-' )
        type = 1;
    if ( a[0] == '-' ) a.erase( a.begin() );
    if ( b[0] == '-' ) b.erase( b.begin() );
    int n = (int)( a.length() ), m = (int)( b.length() );
    string ans = "";
    long long carry = 0;
    for (int i = n + m - 2; i >= 0; i--){
        long long sum = 0;
        for (int j = 0; j < n; j++){
            if ( i - j >= 0 && i - j < m ){
                sum += 1ll * ( a[j] - '0' ) * 1ll * ( b[i - j] - '0' );
            }
        }
        sum += carry;
        ans += (char)( sum % 10 + '0');
        carry = sum / 10;
    }
    while ( carry ){
        ans += (char)( carry % 10 + '0');
        carry /= 10;
    }
    while ( (int)( ans.length() ) > 1 && ans[ (int)( ans.length() ) - 1 ] == '0') ans.pop_back();
    reverse( ans.begin(), ans.end() );
    if ( type == 1 )
        ans = "-" + ans;
    return ans;
}
