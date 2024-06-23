map<int, int> p;
int phi(int x){
    if (p.count(x)) 
        return p[x];
    int ret = x, z = x;
    for (int i = 2; i*i <= x; i++){
        if (x % i == 0){
            while (x % i == 0) 
                x /= i;
            ret = ret / i * (i-1);
        }
    }
    if (x > 1) 
        ret = ret / x * (x-1);
    return p[z] = ret;
}
