#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4+10;

vector<int> a[maxn];
map<int,int> mp;

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int sz; scanf("%d", &sz);
        a[i].resize(sz);
        for(int& x : a[i])
            scanf("%d", &x), mp[x] = 0;
    }
    int cnt = 0;
    for(auto& it : mp)
        it.second = ++cnt;
    int split = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j+1 < (int)(a[i].size()); j++)
            split += mp[a[i][j]] != mp[a[i][j+1]]-1;
    printf("%d %d\n", split, split + n - 1);
}
