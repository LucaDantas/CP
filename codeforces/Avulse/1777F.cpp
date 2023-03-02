#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

struct PersistentTrie
{
    struct Node
    {
            Node *l, *r; int val;
            Node() : l(nullptr), r(nullptr), val(0) {}
    } *root[maxn];

    int get(Node* node) { return node ? node->val : 0; }

    void init() { root[0] = new Node(); root[0] = upd(root[0], 0, 30); root[maxn-1] = new Node(); }

    Node* upd(Node *base, int x, int b) {
        Node* node = new Node();
        if(base)
            *node = *base;

        ++node->val;

        if(b == -1) return node;
        
        if(x&(1<<b)) node->r = upd(node->r, x, b-1);
        else node->l = upd(node->l, x, b-1);

        return node;
    }

    int find(Node* add, Node* rmv, int x, int b) {
        if(!rmv) rmv = new Node();
        if(b == -1) return 0; // I just return and then recreate the value on the upper levels
        // either node->l or node->r must not be empty, because we should be querying an interval >= 0
        if( ( (x&(1<<b)) && get(add->l) - get(rmv->l)) || !(get(add->r) - get(rmv->r)) )
            return (x&(1<<b))  ^ find(add->l, rmv->l, x, b-1);
        return (1<<b) ^ (x & (1<<b)) ^ find(add->r, rmv->r, x, b-1);
    }
} trie;

int a[maxn], pref[maxn], l[maxn], r[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        trie.init();
        int n; scanf("%d", &n);

        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]), pref[i] = a[i] ^ pref[i-1], l[i] = i-1, r[i] = i+1;
        a[0] = a[n+1] = 0x3f3f3f3f;

        // find the interval where I'm max
        for(int i = 1; i <= n; i++)
            while(a[l[i]] < a[i])
                l[i] = l[l[i]];
        for(int i = n; i >= 1; i--)
            while(a[r[i]] <= a[i])
                r[i] = r[r[i]];
    
        for(int i = 1; i <= n; i++)
            trie.root[i] = trie.upd(trie.root[i-1], pref[i], 30);

        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(l[i] - r[i] == 2) continue;
            if(i-l[i] <= r[i]-i) {
                for(int k = l[i]; k < i; k++)
                    ans = max(ans, trie.find(trie.root[r[i]-1], trie.root[i-1], pref[k] ^ a[i], 30));
            } else {
                for(int k = i; k < r[i]; k++)
                    ans = max(ans, trie.find(trie.root[i-1], trie.root[l[i] ? l[i]-1 : maxn-1], pref[k] ^ a[i], 30));
            }
        }
        printf("%d\n", ans);
    }
}