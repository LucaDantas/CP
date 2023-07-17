#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

int a[maxn], f[maxn];
vector<int> cnt[maxn];

int check(int k) {
    static vector<int> sv; sv.clear();
    for(int i = k; i < maxn; i += k)
        for(auto x : cnt[i])
            sv.push_back(x), sv.push_back(x+i);
    sort(sv.begin(), sv.end());
    sv.erase(unique(sv.begin(), sv.end()), sv.end());
    static map<int,int> mp; mp.clear();
    for(auto x : sv)
        mp[x%k]++;
    int tem = 0;
    for(auto it : mp)
        tem += it.second-1;
    return tem;
}

int main() {
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(cnt[abs(a[i]-a[j])].size() <= k*(k+1)/2)
                cnt[abs(a[i]-a[j])].push_back(min(a[i], a[j]));
    for(int i = 1; i < maxn; i++)
        for(int j = i; j < maxn; j += i)
            f[i] += cnt[j].size();
    for(int i = 1; i < maxn; i++)
        if(f[i] <= (k+1)*k/2 && check(i) <= k) return (printf("%d\n", i), 0);
}
