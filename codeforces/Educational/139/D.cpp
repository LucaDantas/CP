#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e7+10;

int f[maxn];

vector<int> pr;

void calc() {
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) f[i] = i, pr.push_back(i);
        for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && i*pr[j] < maxn; j++)
            f[i*pr[j]] = pr[j];
    }
}

vector<int> div(int x) {
    vector<int> a;
    while(x>1)
        a.push_back(f[x]), x /= f[x];
    return a;
}

int main() {
    calc();
    int t; scanf("%d", &t);
    while(t--) {
        int x, y; scanf("%d %d", &x, &y);
        int ans = 0x3f3f3f3f;
        vector<int> dv = div(y-x);
        for(int d : dv)
            ans = min(ans, (d - (x%d))%d);
        printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    }
}
