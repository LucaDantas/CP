#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x; scanf("%d %d", &n, &x);
    vector<int> a(n);
    for(int& x : a)
        scanf("%d", &x);
    int ans = 0, now = 0;
    for(int i = 1; i < n; i++)
        if(a[i] - a[i-1] <= x) ++now, ans = max(ans, now);
        else now = 0;
    printf("%d\n", ans+1);
}
