#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, logn = 29, mod = 998244353;

int cnt = 1;
struct Node {
    int filho[2]{}, sz;
} trie[maxn * logn];

int get(int x, bool lado) { return trie[x].filho[lado] == 0 ? trie[x].filho[lado] = ++cnt : trie[x].filho[lado]; }

void insert(int x) {
    int idx = 1;
    for(int l = logn; l >= -1; l--) {
        trie[idx].sz++;
        if(~l) idx = get(idx, x&(1<<l));
    }
}

int inv(int x) {
    int ans = 1, e = mod-2;
    while(e) {
        if(e&1) ans = (int)(1ll * ans * x % mod);
        x = (int)(1ll * x * x % mod);
        e >>= 1;
    }
    return ans;
}

int ans = 0;

void traverse(int x, int lvl, int val) {
    if(!trie[x].sz || lvl == -1) return;

    ans += 1ll * (trie[trie[x].filho[0]].sz + trie[trie[x].filho[1]].sz) * trie[trie[x].filho[1]].sz % mod;
    ans %= mod;

    for(int k : {0, 1})
        traverse(trie[x].filho[k], lvl-1, val | (k << lvl));
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        for(int i = 0, x; i < n; i++)
            scanf("%d", &x), insert(x);
        traverse(1, logn, 0);
        printf("%d\n", (int)(1ll * ans * inv(n) % mod * inv(n) % mod) + 1);

        for(int i = 1; i <= cnt; i++)
            trie[i].filho[0] = trie[i].filho[1] = trie[i].sz = 0;
        ans = 0;
        cnt = 1;
    }
}
