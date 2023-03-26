#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50010;

int ans[maxn];
map<int,int> last;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int m; scanf("%d", &m);
        for(int i = 0; i <= m; i++)
            ans[i] = -1;
        last.clear();

        for(int i = 1; i <= m; i++) {
            int n; scanf("%d", &n);
            for(int j = 0, v; j < n; j++)
                scanf("%d", &v), last[v] = i;
        }
        for(auto it : last)
            ans[it.second] = it.first;
        bool ok = 1;
        for(int i = 1; i <= m; i++)
            ok &= ans[i] != -1;
        if(ok)
            for(int i = 1; i <= m; i++)
                printf("%d%c", ans[i], " \n"[i==m]);
        else
            puts("-1");
    }
}
