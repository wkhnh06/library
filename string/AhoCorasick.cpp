const int N = 2e5 + 5;

typedef pair< int, int > ii;

struct Trie{
    int a[26], id;
    Trie(){
        for (int i = 0; i < 26; i++)
            a[i] = -1;
        id = 0;
    }
};

vector<Trie> trie;

int cnt, f[N];

string s[N];

vector< ii > vec;

queue<int> q;

void automaton(){
    trie.clear();
    trie.pb(Trie());
    for (int i = 0; i < N; i++)
        f[i] = -1;
    for (int i = 0; i < vec.size(); i++){
        int p = 0;
        string g = s[vec[i].fi];
        for (int j = 0; j < g.size(); j++){
            int c = g[j];
            if (trie[p].a[c - 'a'] == -1){
                trie[p].a[c - 'a'] = ++cnt;
                trie.pb(Trie());
            }
            p = trie[p].a[c - 'a'];
        }
        trie[p].id += vec[i].se;
    }
    f[0] = 0;
    for (int j = 0; j < 26; j++){
        if (trie[0].a[j] == -1)
            trie[0].a[j] = 0;
    }
    for (int j = 0; j < 26; j++){
        if (trie[0].a[j] != 0){
            f[trie[0].a[j]] = 0;
            q.push(trie[0].a[j]);
        }
    }
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++){
            int v = trie[u].a[i];
            if (v != -1){
                int failure = f[u];
                while (trie[failure].a[i] == -1)
                    failure = f[failure];
                failure = trie[failure].a[i];
                f[v] = failure;
                trie[v].id += trie[f[v]].id;
                q.push(v);
            }
        }
    }
}

int travel(int p, int c){
    int org = p;
    if (trie[p].a[c] != -1)
        p = trie[p].a[c];
    else {
        while (trie[p].a[c] == -1)
            p = f[p];
        p = trie[p].a[c];
        trie[org].a[c] = p;
    }
    return p;
}
