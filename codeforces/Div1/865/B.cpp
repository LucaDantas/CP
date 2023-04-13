#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        printf("+ %d\n", n); // make them into a line
        fflush(stdout);
        int trash; scanf("%d", &trash);
        assert(trash != -2);

        printf("+ %d\n", n+1); // make them into a line
        fflush(stdout);
        scanf("%d", &trash);
        assert(trash != -2);
        
        printf("? 1 %d\n", n); fflush(stdout);
        int d; scanf("%d", &d);

        vector<pair<int,int>> p[2]{};
        for(int i = 2, d1, dn; i < n; i++) {
            printf("? 1 %d\n", i);
            fflush(stdout);
            scanf("%d", &d1);

            printf("? %d %d\n", n, i);
            fflush(stdout);
            scanf("%d", &dn);

            if(d1 + dn == d || d1 > dn)
                p[1].push_back({d1, i});
            else if(d1 < dn)
                p[0].push_back({d1, i});
        }
        p[1].push_back({d, n});

        vector<int> ans;
        sort(p[0].begin(), p[0].end(), greater<>());
        sort(p[1].begin(), p[1].end());
        for(auto [val, x] : p[0])
            ans.push_back(x);
        ans.push_back(1);
        for(auto [val, x] : p[1])
            ans.push_back(x);

        auto print = [&](const vector<int>& a) {
            vector<int> perm(n);
            int cnt = 1; // 1-indexado
            for(int i = n-2; i >= 0; i -= 2, cnt++)
                perm[a[i]-1] = cnt;
            for(int i = !(n&1); i < n; i += 2, cnt++)
                perm[a[i]-1] = cnt;
            for(int x : perm)
                printf(" %d", x);
        };
        putchar('!');
        print(ans);
        reverse(ans.begin(), ans.end());
        print(ans);
        puts("");
        fflush(stdout);
        scanf("%d", &trash);
    }
}
