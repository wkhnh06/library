struct Trie {
    int st, f, en;
    map< int, int > a;
    vector<int> graph;
    Trie(){
        graph.clear();
        a.clear();
        st = 0, en = 0, f = 0;
    }
};

struct Aho {
    vector< Trie > aho;
    Aho(){
        aho.pb( Trie() );
    }
    void reset(){
        for (int i = 0; i < aho.size(); i++)
            aho[i].graph.clear();
    }
    void update(string s){
        int p = 0;
        for (int i = 0; i < (int)(s.length()); i++){
            int ch = s[i] - 'A';
            if (aho[p].a.count(ch) == 0){
                aho[p].a[ch] = aho.size();
                aho.pb(Trie());
            }
            p = aho[p].a[ch];
        }
    }
    void automaton(){
        queue<int> q;
        for (int i = 0; i < 26; i++){
            if (aho[0].a.count(i)){
                aho[0].graph.pb(aho[0].a[i]);
                q.push(aho[0].a[i]);
            }
        }
        for (int i = 0; i < 26; i++){
            if (aho[0].a.count(i) == 0)
                aho[0].a[i] = 0;
        }
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++){
                if (aho[u].a.count(i)){
                    int v = aho[u].a[i];
                    int climb = aho[u].f;
                    while (aho[climb].a.count(i) == 0)
                        climb = aho[climb].f;
                    climb = aho[climb].a[i];
                    aho[v].f = climb;
                    aho[climb].graph.pb(v);
                    q.push(v);
                }
            }
        }
    }
    void build_tree(int p){
        aho[p].st = ++cnt;
        for (int i = 0; i < (int)(aho[p].graph.size()); i++){
            int v = aho[p].graph[i];
            build_tree(v);
        }
        aho[p].en = cnt;
    }
    int travel(int p, int ch){
        if (aho[p].a.count(ch) != 0)
            return aho[p].a[ch];
        else {
            int org = p;
            while (aho[p].a.count(ch) == 0)
                p = aho[p].f;
            p = aho[p].a[ch];
            aho[org].a[ch] = p;
            return p;
        }
    }
};
