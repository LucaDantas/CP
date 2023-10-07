#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int f[maxn];
vector<int> pr;

void pre() {
    f[0] = f[1] = 1;
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) f[i] = i, pr.push_back(i);
        for(int j = 0; j < (int)(pr.size()) && pr[j] <= f[i] && i * pr[j] < maxn; j++)
            f[i * pr[j]] = pr[j];
    }
}

int main() {
    pre();
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<bool> mark(n+1);
        vector<int> last_grp(n+1);
        vector<pair<int,int>> ans;
        for(int i = n; i >= 2; i--) if(i%2) {
            // so os impares
            if(!last_grp[f[i]])
                last_grp[f[i]] = i;
            else
                ans.push_back({last_grp[f[i]], i}),
                last_grp[f[i]] = 0;
            if(f[i] == i && last_grp[f[i]] && 2*i <= n) {
                mark[2*i] = 1;
                ans.push_back({i, 2*i});
            }
        }
        for(int i = 2, last = 0; i <= n; i += 2) if(!mark[i]) {
            if(last)
                ans.push_back({last, i}),
                last = 0;
            else
                last = i;
        }
        printf("%ld", ans.size());
        for(auto [x, y] : ans)
            printf(" %d %d", x, y);
        puts("");
    }
}
