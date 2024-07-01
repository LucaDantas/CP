#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5+10;

multiset<pair<int,int>> grp[2][maxn];
vector<int> ans[2];

void lixo() {
    puts("impossible");
    exit(0);
}

int main() {
    int n; scanf("%d", &n);
    for(int rep = 0; rep < 2; rep++) {
        vector<int> opa;
        map<int,int> mp;
        for(int i = 0; i < n; i++) {
            int p; scanf("%d", &p);
            opa.push_back(p);
            mp[p] = 0;
        }
        int cnt = 0;
        for(auto &it : mp)
            it.second = ++cnt;
        for(int i = 0; i < n; i++) {
            int h; scanf("%d", &h);
            grp[rep][mp[opa[i]]].insert({h, i+1});
        }
    }
    for(int i = 1, p1 = 1, p2 = 1; i <= n; i++) {
        if(grp[0][p1].empty()) ++p1;
        if(grp[1][p2].empty()) ++p2;
        if(grp[0][p1].size() < grp[1][p2].size()) {
            auto [h, id] = *grp[0][p1].begin();
            grp[0][p1].erase(grp[0][p1].begin());
            auto it = grp[1][p2].lower_bound({h, -1});
            if(it == grp[1][p2].begin()) lixo();
            auto [h2, id2] = *(--it);
            grp[1][p2].erase(it);
            ans[0].push_back(id);
            ans[1].push_back(id2);
        } else {
            auto [h, id] = *grp[1][p2].begin();
            grp[1][p2].erase(grp[1][p2].begin());
            auto it = grp[0][p1].upper_bound({h, 0x3f3f3f3f});
            if(it == grp[0][p1].end()) lixo();
            auto [h2, id2] = *it;
            grp[0][p1].erase(it);
            ans[0].push_back(id2);
            ans[1].push_back(id);
        }
    }
    for(int rep = 0; rep < 2; rep++) {
        for(int x : ans[rep])
            printf("%d ", x);
        puts("");
    }
}
