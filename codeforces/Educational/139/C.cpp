#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

char s1[maxn], s2[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        scanf(" %s %s", s1, s2);
        int p = 0;
        bool ok = 1;
        for(int i = 0; i < n; i++) {
            int aq = (s1[i]=='B') + (s2[i]=='B')*2;
            if(aq != 3) {
                if(!p) p = aq;
                ok &= p == aq;
            } else if(p) p ^= aq;
        }
        puts(ok ? "YES" : "NO");
    }
}
