#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

constexpr int maxn = 2e5+10;

void solve_even(vector<int>& a) {
    int n = (int)a.size() / 2;
    int l = INT_MAX, r = 0;
    for(int i = 0; i < n/2; i++) {
        int aql = 0, aqr = INT_MAX;
        for(int k = 0; k < 2; k++, swap(a[2*i], a[2*i+n])) {
            int v1 = a[2*i] + a[2*i+1];
            int v2 = a[2*i+n] + a[2*i+1+n];
            if(v1 > v2)
                swap(v1, v2);
            aql = max(aql, v1);
            aqr = min(aqr, v2);
        }
        l = min(aql, l);
        r = max(aqr, r);
    }
    printf("%d\n", r-l);
}

void reorder(vector<int>& a, int n) {
    vector<int> aux(a.size());
    for(int i = 0, pos = 0; i < 2*n; i += 2) {
        aux[i] = a[pos], aux[i+1] = a[pos+1];
        pos = (pos + 1 + n) % (n<<1);
    }
    swap(a, aux);
}

struct SegmentTree {
    vector<pair<int,int>> tree[4*maxn]; // quais sao os pares possiveis de inicio/fim
    void update(int node, int i, int j, int pos, pair<int,int> valor, bool op) {
        if(i == j) {
            if(op) {
                // inserir o valor
                tree[node].push_back(valor);
            } else {
                // remover o valor
                vector<pair<int,int>> aux;
                for(pair<int,int> p : tree[node])
                    if(p != valor)
                        aux.push_back(p);
                swap(tree[node], aux);
            }
            return;
        }

        int m = (i+j)>>1;
        if(pos <= m)
            update(node<<1, i, m, pos, valor, op);
        else
            update(node<<1|1, m+1, j, pos, valor, op);

        // merge
        tree[node].clear();
        for(auto pl : tree[node<<1])
            for(auto pr : tree[node<<1|1])
                if(pl.second != pr.first)
                    tree[node].push_back({pl.first, pr.second});

        // limpar, tenho que evitar repeticoes
        sort(tree[node].begin(), tree[node].end());
        tree[node].erase(unique(tree[node].begin(), tree[node].end()), tree[node].end());
    }
    bool tem() {
        for(auto [l, r] : tree[1])
            if(l != r) return 1;
        return 0;
    }
    void clear(int n) {
        for(int i = 1; i <= 4*n; i++)
            tree[i].clear();
    }
} seg;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n<<1);
        for(int i = 0; i < 2*n; i++)
            scanf("%d", &a[i]);
        if(!(n&1)) {
            solve_even(a);
            continue;
        }
        reorder(a, n);

        vector<array<int,3>> pares_possiveis;
        for(int i = 0; i < n; i++)
            for(int v1 : {2*i, (2*i-1+2*n)%(2*n)})
                for(int v2 : {2*i+1, (2*i+2)%(2*n)})
                    pares_possiveis.push_back({i, v1, v2});

        auto val = [&](array<int,3> p) {
            return a[p[1]] + a[p[2]];
        };
        sort(pares_possiveis.begin(), pares_possiveis.end(), [&val](auto& a, auto& b){
            return val(a) < val(b);
        });

        int ans = INT_MAX;
        for(int i = 0, ptr = 0; i < 4*n; i++) {
            for(; ptr < 4*n && !seg.tem(); ptr++)
                seg.update(1, 0, n-1, pares_possiveis[ptr][0], {pares_possiveis[ptr][1], pares_possiveis[ptr][2]}, 1); // insert na seg
            if(seg.tem())
                ans = min(ans, val(pares_possiveis[ptr-1])-val(pares_possiveis[i]));
            seg.update(1, 0, n-1, pares_possiveis[i][0], {pares_possiveis[i][1], pares_possiveis[i][2]}, 0); // tira da seg
        }
        printf("%d\n", ans);
        seg.clear(n);
    }
}
