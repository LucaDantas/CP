#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int n;
int a[maxn], p[maxn], dist[maxn], fim[maxn], cnt[maxn];

int get(int k) {
    memset(cnt, 0, sizeof cnt);
    for(int i = 0, ptr = 0; i < n; i++) {
        for(; cnt[a[ptr%n]]+1 <= k && ptr-i < n; ptr++)
            cnt[a[ptr%n]]++;
        p[i] = ptr%n;
        --cnt[a[i]];
    }
    for(int i = n-1; i >= 0; i--) {
        if(p[i] <= i) dist[i] = 0, fim[i] = i;
        else dist[i] = dist[p[i]]+1, fim[i] = fim[p[i]];
    }
    int ans = n;
    for(int i = n-1; i >= 0; i--)
        if(p[i] <= i) ans = min(ans, 1 + dist[p[i]] + (fim[p[i]] < i));
    return ans;
}

int ans[maxn];

void solve(int l, int r, int ans_l, int ans_r) {
    if(l > r) return;
    int m = (l+r) >> 1;
    if(ans_l == ans_r) ans[m] = ans_l;
    else ans[m] = get(m);
    solve(l, m-1, ans_l, ans[m]);
    solve(m+1, r, ans[m], ans_r);
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    solve(1, n, n, 1);
    for(int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
}
