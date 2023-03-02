#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

int ans[maxn];

bool check(int a) {
    int cnt = 0;
    while(a)
        cnt += (a%10) > 0, a /= 10;
    return cnt == 1;
}

int main() {
    for(int i = 1; i < maxn; i++)
        ans[i] = ans[i-1] + check(i);
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
}
