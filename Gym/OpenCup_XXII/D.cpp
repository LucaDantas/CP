#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

int val_l[maxn], val_c[maxn], ans;

vector<pair<int,int>> set_l[maxn], set_c[maxn];

void testa(int a[]) {
    multiset<int> mx; mx.insert(0), mx.insert(0), mx.insert(0);
    for(int i = 0; i < maxn; i++)
        if(a[i])
            mx.insert(a[i]), mx.erase(mx.begin());
    ans = max(ans, *mx.begin() + *next(mx.begin()) + *next(next(mx.begin())));
}

void testa2(int a[], int opa[], vector<pair<int,int>> b[]) {
    multiset<int> mx;
    for(int i = 0; i < maxn; i++)
        mx.insert(a[i]);
    for(int i = 0; i < maxn; i++) {
        if(!b[i].size()) continue;
        for(auto [pos, val] : b[i]) {
            mx.erase(mx.find(a[pos]));
            a[pos] -= val;
            mx.insert(a[pos]);
        }
        ans = max(ans, opa[i] + *mx.rbegin() + *next(mx.rbegin()));
        for(auto [pos, val] : b[i]) {
            mx.erase(mx.find(a[pos]));
            a[pos] += val;
            mx.insert(a[pos]);
        }
    }
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int l, c, v; scanf("%d %d %d", &l, &c, &v);
        val_l[l] += v, val_c[c] += v;
        set_l[l].push_back(pair<int,int>(c, v));
        set_c[c].push_back(pair<int,int>(l, v));
    }
    testa(val_l), testa(val_c);
    testa2(val_c, val_l, set_l), testa2(val_l, val_c, set_c);
    printf("%d\n", ans);
}
