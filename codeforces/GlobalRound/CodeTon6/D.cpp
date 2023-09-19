#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<pair<int,int>> c = {{0, 0}};
        for(int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            while(c.size() && c.back().first >= x)
                c.pop_back();
            c.push_back({x, i});
        }
        vector<int> a(n+1);
        a[0] = 0x3f3f3f3f;
        int k; scanf("%d", &k);
        for(int i = 1; i < (int)(c.size()); i++) {
            int qtd = min(k / (c[i].first - c[i-1].first), a[c[i-1].second]);
            k -= qtd * (c[i].first - c[i-1].first);
            a[c[i].second] += qtd;
            a[c[i-1].second] -= qtd;
        }
        for(int i = n-1; i >= 1; i--)
            a[i] += a[i+1];
        for(int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        puts("");
    }
}
