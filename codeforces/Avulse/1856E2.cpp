#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

vector<int> g[maxn];
int sz[maxn], maior[maxn], p[maxn];
long long ans = 0;

void pre(int n) {
    map<int,int> cnt;
    for(int x : g[n])
        cnt[x]++;
    for(auto it = cnt.begin(); it != cnt.end(); it = next(it))
        while(it->second > 2) cnt[it->first<<1]++, it->second -= 2;
    g[n].clear();
    for(auto it : cnt)
        while(it.second--) g[n].push_back(it.first);
}

template<int len = 1>
void calc(int n) {
    if(len*2 < sz[n])
        return calc<std::min(2*len, maxn)>(n);

    bitset<len+1> dp;
    dp[0] = 1;
    for(int x : g[n])
        dp |= dp << x;
    for(int i = sz[n]/2; i >= 0; i--)
        if(dp[i]) return (void)(ans += 1ll * i * (sz[n] - i));
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 2; i <= n; i++)
        scanf("%d", p+i);
    for(int i = n; i >= 1; i--) {
        if(maior[i]*2 < sz[i])
            pre(i), calc(i);
        else
            ans += 1ll * maior[i] * (sz[i] - maior[i]);
        ++sz[i];
        g[p[i]].push_back(sz[i]);
        sz[p[i]] += sz[i];
        maior[p[i]] = max(maior[p[i]], sz[i]);
    }
    printf("%lld\n", ans);
}
