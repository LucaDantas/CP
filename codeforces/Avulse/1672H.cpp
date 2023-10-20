#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int fdd[maxn][2];

int main() {
    int n, q; scanf("%d %d", &n, &q);
    int last = -1;
    for(int i = 1; i <= n; i++) {
        char c; scanf(" %c", &c);
        int val = c == '1';
        fdd[i][0] = fdd[i-1][0];
        fdd[i][1] = fdd[i-1][1];
        if(last == val)
            fdd[i][val]++;
        last = val;
    }
    puts("");
    while(q--) {
        int l, r; scanf("%d %d", &l, &r);
        printf("%d\n", 1 + max(fdd[r][0] - fdd[l][0], fdd[r][1] - fdd[l][1]));
    }
}
