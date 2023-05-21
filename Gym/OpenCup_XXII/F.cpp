#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 3e5+10;

int a[maxn];
char s[maxn];

vector<int> valores;

int32_t main() {
    int n; scanf("%lld", &n);
    scanf(" %s", s);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    for(int i = 1; i < n; i++)
        if(s[i] == s[i-1])
            a[i] = max(a[i], a[i-1]);
    bool foi = 0;
    for(int i = 1; i < n-1; i++) {
        foi |= s[i] != s[i-1];
        if(foi && s[i] != s[i+1])
            valores.push_back(a[i]);
    }
    long long ans = 0;
    sort(valores.begin(), valores.end(), greater<int>());
    for(int i = 0; i < (valores.size()+1) / 2; i++)
        ans += valores[i];
    printf("%lld\n", ans);
}
