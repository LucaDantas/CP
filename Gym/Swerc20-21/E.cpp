#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    int ans = 1e5+10;
    for(int i = 0, a, b; i < n; i++)
        scanf("%d %d", &a, &b), ans = min(ans, b / a);
    printf("%d\n", ans);
}