#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<array<int,3>> a;
        long long sB = 0, s[2]{};
        for(int i = 1, x, y; i <= 2*n-1; i++)
            scanf("%d %d", &x, &y), sB += y, a.push_back({x, y, i});
        sort(a.begin(), a.end(), greater<>());
        for(int i = 1; i < 2*n-1; i++)
            s[i&1] += a[i][1];
        puts("YES");
        printf("%d", a[0][2]);
        if(s[0] >= s[1])
            for(int i = 2; i < 2*n-1; i += 2)
                printf(" %d", a[i][2]);
        else
            for(int i = 1; i < 2*n-1; i += 2)
                printf(" %d", a[i][2]);
        puts("");
    }
}
