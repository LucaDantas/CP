#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 55*55;

vector<int> a[maxn];

int ans[maxn], n, k;

int id(int i, int j) { return i*n + j; }

int dist(int l, int r) {
    return abs(l/n - r/n) + abs(l%n - r%n);
}

int main() {
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int val; scanf("%d", &val);
            a[val].push_back(id(i, j));
        }
    }
    memset(ans, 0x3f, sizeof ans);
    for(int l : a[1])
        ans[l] = 0;
    for(int val = 2; val <= k; val++)
        for(int l : a[val]) for(int r : a[val-1])
            ans[l] = min(ans[l], ans[r] + dist(l, r));
    int vapo = 0x3f3f3f3f;
    for(int l : a[k])
        vapo = min(vapo, ans[l]);
    printf("%d\n", vapo == 0x3f3f3f3f ? -1 : vapo);
}