#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

char s[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        scanf(" %s", s);
        static set<int> apareceu; apareceu.clear();
        if(n <= 3) { puts("NO"); continue; }
        apareceu.insert((s[0]-'a') + (s[1]-'a') * 26);
        bool ok = 0;
        for(int i = 2; i+1 < n; i++) {
            ok |= apareceu.count((s[i]-'a') + (s[i+1]-'a')*26);
            apareceu.insert((s[i-1]-'a') + (s[i]-'a')*26);
        }
        puts(ok ? "YES" : "NO");
    }
}
