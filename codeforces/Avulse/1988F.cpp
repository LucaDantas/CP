#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())

constexpr int maxn = 1e5+10, logn = 20, logv = 30, inf = INT_MAX;

struct Node {
    int val, qtd; // menor valor na minha subarvore (ou se so tiver um o valor desse cara) e quantos caras tem la
    int left, right;
    Node() : val(INT_MAX), qtd(0), left(-1), right(-1) {} 
} trie[2 * maxn * logn];

int cnt = 1;

int get(int &node) { if(node == -1) node = ++cnt; return node; }

void upd_val(int node) {
    trie[node].qtd = trie[get(trie[node].left)].qtd + trie[get(trie[node].right)].qtd;

    if(trie[node].qtd == 2 && trie[trie[node].left].qtd==1 && trie[trie[node].right].qtd==1)
        trie[node].val = trie[trie[node].left].val ^ trie[trie[node].right].val;

    else if(trie[node].qtd == 1)
        trie[node].val = min(trie[trie[node].left].val, trie[trie[node].right].val);

    else
        trie[node].val = min(trie[trie[node].left].qtd >= 2 ? trie[trie[node].left].val : INT_MAX,
                             trie[trie[node].right].qtd >= 2 ? trie[trie[node].right].val : INT_MAX);
}

void upd(int node, int x, int b, int val) {
    if(b == -1) {
        trie[node].qtd += val;
        if(trie[node].qtd >= 2)
            trie[node].val = 0;
        else if(trie[node].qtd == 1)
            trie[node].val = x;
        else if(!trie[node].qtd)
            trie[node].val = INT_MAX;
        return;
    }

    if(x & (1 << b))
        upd(get(trie[node].right), x, b-1, val);
    else
        upd(get(trie[node].left), x, b-1, val);

    upd_val(node);
}

long long check(int val, vector<int>& a) {
    long long ans = 0;
    for(int l = 0, r = 0; l < sz(a); l++) {
        for(; r < sz(a) && (trie[1].qtd <= 1 || trie[1].val > val); r++)
            upd(1, a[r], logv, 1);
        ans += sz(a)-r+(trie[1].qtd >= 2 && trie[1].val <= val);
        upd(1, a[l], logv, -1); // removo o cara
    }
    return ans;
}

void clear(int node = 1) {
    if(node == -1) return;
    clear(trie[node].left);
    clear(trie[node].right);
    trie[node] = Node();
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; long long k; scanf("%d %lld", &n, &k);
        vector<int> a(n);
        for(int& x : a)
            scanf("%d", &x);
        
        int l=0,r=inf, ans = -1;
        while(l <= r) {
            int m = l + (r-l)/2;
            if(check(m, a) >= k)
                ans = m, r = m-1;
            else
                l = m+1;
        }

        printf("%d\n", ans);
    }
}
