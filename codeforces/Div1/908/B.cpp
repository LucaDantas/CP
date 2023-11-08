#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),(a).end()

struct BIT {
    vector<int> bit;
    int sz;
    BIT(int n) : bit(n+10) { sz = n+10; }
    void upd(int x, int v) {
        for(x++; x > 0; x -= x&-x)
            bit[x] = max(bit[x], v);
    }
    int query(int x) {
        int ans = 0;
        for(x++; x < sz; x += x&-x)
            ans = max(ans, bit[x]);
        return ans;
    }
};

struct LIS {
    vector<int> dp;
    int mx = 0;
    LIS(vector<int> a, int sz) : dp(sz(a)) {
        BIT bit(sz);
        for(int i = sz(a)-1; i >= 0; i--) {
            dp[i] = bit.query(a[i]+1)+1;
            bit.upd(a[i], dp[i]);
            mx = max(mx, dp[i]);
        }
    }
};

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, m; scanf("%d %d", &n, &m);
        vector<int> a(n), b(m);

        map<int,int> mp;

        for(int& x : a)
            scanf("%d", &x), mp[x]++;
        for(int& x : b)
            scanf("%d", &x), mp[x]++;

        sort(all(b), greater<int>());

        int cnt = 0;
        for(auto& it : mp)
            it.second = cnt++;
        vector<int> back(cnt);
        for(int& x : a)
            back[mp[x]] = x, x = mp[x];
        for(int& x : b)
            back[mp[x]] = x, x = mp[x];

        int ptr = 0;
        LIS lis(a, cnt);
        vector<int> ans;

        for(int i = 0; i < n; i++) {
            if(lis.dp[i] == lis.mx)
                for(; ptr < m && b[ptr] >= a[i]; ptr++)
                    ans.push_back(b[ptr]);
            ans.push_back(a[i]);
        }

        for(; ptr < m; ptr++)
            ans.push_back(b[ptr]);
        for(int x : ans)
            printf("%d ", back[x]);
        puts("");
        // LIS lis2(ans, cnt);
        // printf("mx %d -> %d\n", lis.mx, lis2.mx);
    }
}
