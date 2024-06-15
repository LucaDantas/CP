#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10, logn = 21;

struct PersistentSegTree {
    struct Node {
        int left = 0, right = 0;
        int qtd = 0;
    } tree[maxn * logn];

    int pai[maxn][logn], ctr, ctr_pais;
    int back[maxn];
    map<int,int> id_pai;

    vector<int> indexes;

    PersistentSegTree() {
        indexes.push_back(1);
        ctr = 1;
        ctr_pais = 1;
        id_pai[1] = 1;
        back[1] = 1;
    }

    int add(int node, int i, int j, int val) {
        tree[++ctr] = tree[node];
        node = ctr;

        if(i == j)
            return tree[node].qtd |= 1, node;

        int m = (i+j)>>1;

        if(val <= m)
            tree[node].left = add(tree[node].left, i, m, val);
        else
            tree[node].right = add(tree[node].right, m+1, j, val);

        tree[node].qtd = tree[tree[node].left].qtd + tree[tree[node].right].qtd;

        return node;
    }

    void add(int val) {
        int new_id = add(indexes.back(), 1, maxn, val);

        ++ctr_pais;

        pai[ctr_pais][0] = id_pai[indexes.back()];

        indexes.push_back(new_id);

        back[ctr_pais] = new_id;
        id_pai[new_id] = ctr_pais;

        for(int l = 1; l < logn; l++)
            pai[ctr_pais][l] = pai[pai[ctr_pais][l-1]][l-1];
    }

    void remove(int k) {
        int cur = id_pai[indexes.back()];
        for(int l = logn-1; l >= 0; l--)
            if(k >= (1 << l))
                cur = pai[cur][l], k -= (1 << l);
        cur = back[cur];
        indexes.push_back(cur);
    }

    void rollback() { indexes.pop_back(); }

    int query() { return tree[indexes.back()].qtd; }
} seg;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        char type; scanf(" %c", &type);
        switch(type) {
        case '+': {
            int x; scanf("%d", &x);
            seg.add(x);
            break;
        }
        case '-': {
            int k; scanf("%d", &k);
            seg.remove(k);
            break;
        }
        case '!':
            seg.rollback();
            break;
        case '?':
            printf("%d\n", seg.query());
            fflush(stdout);
            break;
        default:
            assert(0);
        }
    }
}
