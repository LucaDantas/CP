#include <bits/stdc++.h>
using namespace std;

int dfs(int u, const vector<int>& f, vector<int>& mark) {
    if(mark[f[u]] == -1) return (mark[u] = -1);
    if(mark[f[u]]) {
        int ans = mark[u] - mark[f[u]] + 1;
        mark[u] = -1;
        return ans;
    }
    mark[f[u]] = mark[u]+1;
    int ans = dfs(f[u], f, mark);
    mark[u] = -1;
    return ans;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        vector<int> f(n), mark(n);
        for(int& x : f)
            scanf("%d", &x), --x;
        bool ok = 1;
        for(int i = 0; i < n; i++) {
            if(k == 1) ok &= f[i] == i;
            else if(!mark[i]) {
                mark[i] = 1;
                int aq = dfs(i, f, mark);
                ok &= aq == k || aq == -1;
            }
        }
        puts(ok ? "Yes" : "No");
    }
}
