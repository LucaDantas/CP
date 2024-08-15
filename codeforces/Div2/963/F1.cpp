#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

char s[maxn];


inline void add(int &val, int add, int mod) { val = (val + add + mod) % mod; };

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k, w, h; scanf("%d %d %d %d", &n, &k, &w, &h);
        vector<pair<int,int>> val(1); // starts in the position (0,0)
        scanf(" %s", s);
        for(int i = 0; i < n; i++) {
            pair<int,int> last = val.back();
            switch (s[i]) {
            case 'L':
                add(last.first, -1, 2*w);
                break;
            case 'R':
                add(last.first, 1, 2*w);
                break;
            case 'U':
                add(last.second, 1, 2*h);
                break;
            case 'D':
                add(last.second, -1, 2*h);
                break;
            }
            val.push_back(last);
        }
        map<pair<int,int>, int> cnt;
        pair<int,int> cur = {0,0};
        for(int i = 0; i < k; i++) { // note that the last one isn't added and 0 is added, this is on purpose
            cnt[cur]++;
            add(cur.first, val.back().first, 2*w);
            add(cur.second, val.back().second, 2*h);
        }
        long long ans = 0;
        for(int i = 1; i < val.size(); i++)
            ans += cnt[{(2*w-val[i].first)%(2*w), (2*h-val[i].second)%(2*h)}];
        printf("%lld\n", ans);
    }
}
