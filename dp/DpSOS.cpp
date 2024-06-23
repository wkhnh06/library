const int N = 24;

int dp[(1 << N)];

bool checkBit(int mask, int pos){
    if (mask & (1 << pos))
        return 1;
    else
        return 0;
}

int changeBit(int mask, int pos){
    return (mask ^ (1 << pos));
}

for (int bit = 0; bit < N; bit++){
    for (int mask = 0; mask < (1 << N); mask++){
        if (checkBit(mask, bit))
            dp[mask] += dp[changeBit(mask, bit)];
    }
}

