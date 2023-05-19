#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int match[maxn];
set<int> mark;

int n;
vector<int> a;

bool dfs(int u) {
    if(u >= n)
        return match[u] == -1 || dfs(match[u]);

    vector<int> visitar;

    while(mark.size()) {
        auto it = mark.begin();
        while(it != mark.end() && (*it-n == u || *it-n == a[u]))
            it = next(it);
        if(it == mark.end()) break;
        visitar.push_back(*it);
        mark.erase(it);
    }

    for(int val : visitar) {
        if(dfs(val)) {
            match[u] = val;
            match[val] = u;
            return 1;
        }
    }

    return 0;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 0; i <= 2*n; i++)
            match[i] = -1;

        a.resize(n);
        for(int &x : a)
            scanf("%d", &x);

        vector<int> p(n), q(n);
        vector<int> opa(n); iota(opa.begin(), opa.end(), 0);
        set<int> vivo(opa.begin(), opa.end());

        vector<int> nao_foi;
        for(int i = 0; i < n; i++) {
            --a[i]; // 0-index
            auto it = vivo.begin();
            while(it != vivo.end() && (*it == a[i] || *it == i))
                it = next(it);
            if(it == vivo.end()) {
                nao_foi.push_back(i);
                continue;
            }
            match[i] = *it + n;
            match[*it + n] = i;
            // p[*it] = i;
            // q[a[i]] = *it;
            vivo.erase(it);
        }

        bool ok = 1;
        for(int x : nao_foi) {
            mark.clear();
            for(int i = n; i < 2*n; i++)
                mark.insert(i);
            ok &= dfs(x);
            // printf("%d %d\n", x, match[x]);
        }

        if(!ok) { puts("Impossible"); continue; }
        puts("Possible");

        // for(int i = 0; i < n; i++)
        //     printf("(%d %d) ", i, match[i]);
        // puts("");

        for(int i = 0; i < n; i++)
            p[match[i]-n] = i, q[a[i]] = match[i]-n;

        for(int x : p)
            printf("%d ", x+1);
        puts("");
        for(int x : q)
            printf("%d ", x+1);
        puts("");
        // for(int i = 0; i < n; i++)
        //     printf("%d ", a[p[q[i]]]);
        // puts("");
    }
}
