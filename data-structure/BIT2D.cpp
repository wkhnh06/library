struct BIT2D {
    vector<int> bit[N], fake[N];
    BIT2D(){
        for (int i = 0; i < N; i++)
            bit[i].clear(), fake[i].clear();
    }
    void fakeup(int x, int y){
        while (x < N){
            fake[x].pb(y);
            x += x & (-x);
        }
    }
    void construct(){
        for (int i = 0; i < N; i++){
            sort(fake[i].begin(), fake[i].end());
            fake[i].erase( unique(fake[i].begin(), fake[i].end() ), fake[i].end() );
            bit[i].assign(fake[i].size() + 5, 0);
        }
    }
    void up(int x, int y, int val){
        while (x < N){
            int it = upper_bound(fake[x].begin(), fake[x].end(), y) - fake[x].begin();
            while (it < (int)(bit[x].size())){
                bit[x][it] += val;
                it += it & (-it);
            }
            x += x & (-x);
        }
    }
    int get(int x, int y){
        int sum = 0;
        while (x > 0){
            int it = upper_bound(fake[x].begin(), fake[x].end(), y) - fake[x].begin();
            while (it > 0){
                sum += bit[x][it];
                it -= it & (-it);
            }
            x -= x & (-x);
        }
        return sum;
    }
}bit2d;
