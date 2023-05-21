#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

set<int> pos[maxn];
bool mark[maxn];
int a[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 0, x; i < n; i++)
        scanf("%d", &x), a[i] = x, pos[x].insert(i);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans += !mark[i];
        int x = i;
        while(!mark[x]) {
            mark[x] = 1;
            pos[a[x]].erase(x);
            if(pos[a[x]-1].upper_bound(x) != pos[a[x]-1].end())
                x = *pos[a[x]-1].upper_bound(x);
        }
    }
    printf("%d\n", ans);
}
