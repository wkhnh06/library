#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

typedef pair< int, int > ii;

string s;

const int N = 1e6 + 5;

int root[N], n, q, cnt = 0;

struct Node {
    int Left, Right, val, open, close;
    Node(){
        Left = Right = val = open = close = 0;
    }
}it[25 * N];

Node combine(Node k, Node le, Node ri){
    int tmp = min(le.open, ri.close);
    k.val = le.val + ri.val + 2 * tmp;
    k.open = le.open + ri.open - tmp;
    k.close = le.close + ri.close - tmp;
    return k;
}

void build_tree(int l, int r){
    if (l == r){
        if (s[l] == '(')
            it[cnt].open = 1;
        else
            it[cnt].close = 1;
        return ;
    }
    int md = (l + r) >> 1;
    int cur = cnt;
    it[cur].Left = ++cnt;
    build_tree(l, md);
    it[cur].Right = ++cnt;
    build_tree(md + 1, r);
    it[cur] = combine(it[cur], it[ it[cur].Left ], it[ it[cur].Right ]);
}

void update(int k, int l, int r, int pos){
    if (pos == l && pos == r){
        it[cnt].open = (it[k].open ^ 1);
        it[cnt].close = (it[k].close ^ 1);
        return ;
    }
    int md = (l + r) >> 1, cur = cnt;
    if (pos <= md){
        it[cur].Right = it[k].Right;
        it[cur].Left = ++cnt;
        update(it[k].Left, l, md, pos);
    }
    else {
        it[cur].Right = ++cnt;
        it[cur].Left = it[k].Left;
        update(it[k].Right, md + 1, r, pos);
    }
    it[cur] = combine(it[cur], it[ it[cur].Left ], it[ it[cur].Right ]);
    return ;
}

Node get(int k, int l, int r, int L, int R){
    if (R < l || r < L || L > R) return Node();
    if (L <= l && r <= R)
        return it[k];
    int md = (l + r) >> 1;
    Node tmp;
    Node tmp1 = get(it[k].Left, l, md, L, R);
    Node tmp2 = get(it[k].Right, md + 1, r, L, R);
    return combine(tmp, tmp1, tmp2);
}

int main(){
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    cin >> s;
    n = (int)( s.length() );
    s = "+" + s;
    cnt = 1;
    build_tree( 1, n );
    root[0] = 1;
    cin >> q;
    for (int i = 1; i <= q; i++){
        char type; int pos;
        cin >> type;
        if ( type == 'C' ){
            cin >> pos;
            ++cnt;
            root[i] = cnt;
            update(root[i - 1], 1, n, pos);
        }
        else if ( type == 'Q' ){
            int l, r;
            cin >> l >> r;
            cout << (r - l + 1) - get(root[i - 1], 1, n, l, r).val << "\n";
            root[i] = root[i - 1];
        }
        else {
            cin >> pos;
            root[i] = root[ pos - 1 ];
        }
    }
}

