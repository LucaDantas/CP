#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, logn = 16;

vector<int> dv[maxn];

void calc() {
    for(int i = 1; i < maxn; i++)
        for(int j = i; j < maxn; j += i)
            dv[j].push_back(i);
}

struct Node {
    int mn = 0x3f3f3f3f;
    Node *l = nullptr, *r = nullptr;
    Node* get_left() { return !l ? l = new Node() : l; }
    Node* get_right() { return !r ? r = new Node() : r; }
} *root[maxn];

Node* insert(Node *node, int val, int b) {
    node->mn = min(node->mn, val);
    if(b == -1) return node;
    if(!(val & (1 << b)))
        node->l = insert(node->get_left(), val, b-1);
    else
        node->r = insert(node->get_right(), val, b-1);
    return node;
}

int query(Node *node, int val, int b, int mx) {
    if(node->mn > mx) return -1;
    if(b == -1) return node->mn;
    auto get_l = [&]() -> int { return query(node->get_left(), val, b-1, mx); };
    auto get_r = [&]() -> int { return query(node->get_right(), val, b-1, mx); };
    int p1 = (val & (1 << b)) ? get_l() : get_r();
    if(p1 != -1) return p1;
    return (val & (1 << b)) ? get_r() : get_l();
}

bool mark[maxn];

int main() {
    calc();
    int q; scanf("%d", &q);
    for(int i = 0; i < maxn; i++)
        root[i] = new Node();
    while(q--) {
        int t; scanf("%d", &t);
        if(t == 1) {
            int u; scanf("%d", &u);
            if(mark[u]) continue;
            mark[u] = 1;
            for(int x : dv[u])
                root[x] = insert(root[x], u, logn);
        } else {
            int x, k, s; scanf("%d %d %d", &x, &k, &s);
            if(x % k != 0) { puts("-1"); continue; }
            s -= x;
            printf("%d\n", query(root[k], x, logn, s));
        }
    }
}
