#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

char s[maxn];
int cnt[30], cor[maxn];
vector<pair<int,int>> vizinhos[30];
set<pair<int,int>> q;

struct BIT {
    int n;
    vector<int> bit;
    BIT(int _n) : n(_n), bit(_n+1, 0) {}
    void upd(int x, int v) {
        for(; x <= n; x += x&-x)
            bit[x] += v;
    }
    int query(int x) {
        int ans = 0;
        for(; x > 0; x -= x&-x)
            ans += bit[x];
        return ans;
    }
};

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf(" %s", s);
        int sz = (int)(strlen(s)), tot = 0;
        set<int> caras;
        for(int i = 1; i < sz; i++)
            if(s[i] == s[i-1])
                ++cnt[s[i]-'a'], ++tot, caras.insert(i), cor[i] = s[i]-'a';

        for(int i = 0; i < 26; i++)
            q.insert({cnt[i], i});

        if(caras.size()) for(auto p1 = caras.begin(), p2 = next(p1); p2 != caras.end(); ++p1, ++p2) {
            if(cor[*p1] != cor[*p2])
                vizinhos[cor[*p1]].push_back({*p1, *p2}),
                vizinhos[cor[*p2]].push_back({*p1, *p2});
        }

        vector<pair<int,int>> ans;
        while(caras.size()) {
            int u = q.rbegin()->second;
            if(vizinhos[u].size()) {
                auto [p1, p2] = vizinhos[u].back();

                vizinhos[u].pop_back();

                if(!caras.count(p1) || !caras.count(p2))
                    continue;

                ans.push_back({p1, p2-1}); // intervalo (l, r]

                caras.erase(p1), caras.erase(p2);

                q.erase({cnt[cor[p1]], cor[p1]});
                q.erase({cnt[cor[p2]], cor[p2]});
                if(--cnt[cor[p1]])
                    q.insert({cnt[cor[p1]], cor[p1]});
                if(--cnt[cor[p2]])
                    q.insert({cnt[cor[p2]], cor[p2]});
                
                auto prev = caras.lower_bound(p1);
                auto prox = caras.upper_bound(p2);

                if(prev != caras.begin() && prox != caras.end() && cor[*(--prev)] != cor[*prox]) {
                    vizinhos[cor[*prev]].push_back({*prev, *prox});
                    vizinhos[cor[*prox]].push_back({*prev, *prox});
                }
            } else {
                int last = *caras.begin();
                caras.insert(sz);
                for(auto it = next(caras.begin()); it != caras.end(); it++) {
                    ans.push_back({last, *it-1});
                    last = *it;
                }
                caras.clear();
            }
        }

        BIT bit(sz);

        printf("%ld\n", ans.size()+1);
        for(auto [l, r] : ans) {
            ++l, ++r; // 1-indexed in the bit
            int tl = l - bit.query(l), tr = r - bit.query(r);
            bit.upd(l, tr-tl+1);
            printf("%d %d\n", tl, tr);
        }
        printf("%d %d\n", 1, sz-bit.query(sz));

        q.clear();
        for(int i = 0; i < 30; i++)
            cnt[i] = 0, vizinhos[i].clear();
    }
}
