#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

int main() {
    int maxsz, k; scanf("%d %d\n", &maxsz, &k);
    vector<pair<int,int>> now, nxt;
    now = {{0, 1}};

    for(int n = 1; n <= min(maxsz, k); n++) {
        int left = 0, right = 0, active = 0;

        for(int i = n; i - k <= now.back().first; i += n) {
            while(right < (int) now.size() && now[right].first < i) {
                active += now[right].second;
                active %= mod;
                right++;
            }

            while(left < (int) now.size() && now[left].first < i - k) {
                active += mod - now[left].second;
                active %= mod;
                left++;
            }

            if(active > 0)
                nxt.push_back({i, active});
        }

        swap(now, nxt);
        nxt.clear();
    }
    int ans = 0;
    for(auto [pos, cnt] : now)
        ans += cnt, ans %= mod;
    printf("%d\n", ans);
}
