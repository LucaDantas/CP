#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        long long ans = 0;
        int n; scanf("%d", &n);
        vector<int> a(n), b(n);
        for(int& x : a)
            scanf("%d", &x);
        for(int& x : b)
            scanf("%d", &x);
        vector<map<int,int>> cnt(n+1);
        for(int i = 0; i < n; i++)
            cnt[a[i]][b[i]]++;
        vector<vector<pair<int,int>>> opa(n+1);
        for(int i = 1; i <= n; i++)
            for(auto it : cnt[i]) {
                opa[i].push_back(it);
                if(1ll*i*i == it.first*2)
                    ans += 1ll*it.second*(it.second-1)/2;
            }
        for(int i = 1; i <= n && 1ll*i*i <= 2*n; i++) {
            {
                int val = i*i;
                for(auto it : opa[i]) if(2*it.first < val) {
                    auto pega = lower_bound(all(opa[i]), make_pair(val - it.ff, 0));
                    if(pega != opa[i].end() && pega->ff == val-it.ff)
                        ans += 1ll * it.ss * pega->ss;
                }
            }
            for(int j = i+1; j <= n && 1ll*j*i <= 2*n; j++) {
                int val = j*i;
                for(auto it : opa[j]) {
                    auto pega = lower_bound(all(opa[i]), make_pair(val - it.ff, 0));
                    if(pega != opa[i].end() && pega->ff == val-it.ff)
                        ans += 1ll * it.ss * pega->ss;
                }
            }
        }
        printf("%lld\n", ans);
    }
}
