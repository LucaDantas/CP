#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int maxn = 5e5 + 10;

char s[maxn];

// lib de naim
vector<int> manacher(int n) {
    vector<int> d2(n+1);
    for(int i=0,l=0,r=-1;i<n;i++){
        int k = (i>r) ? 0 : min(d2[l+r-i+1],r-i+1);
        
        while(0<=i-k-1 && i+k<n && s[i-k-1]==s[i+k]){
            k++;
        }
        d2[i] = k--;
        if(i+k>r){
            r = i+k;
            l = i-k-1;
        }
    } //palindromo de tamanho par;
    return d2;
}

struct DSU {
    int pai[maxn], peso[maxn];
    void init(int n) { iota(pai, pai+n+1, 0); fill(peso, peso+n+1, 1); }
    int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
    void join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return;
        if(peso[a] < peso[b])
            swap(a, b);
        pai[b] = a;
        peso[a] += peso[b];
    }
} dsu;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n); dsu.init(n);
        scanf(" %s", s);
        vector<int> a = manacher(n);
        priority_queue<pair<int,int>> ativos;
        for(int i = 0; i <= n; i++) {
            while(ativos.size() && ativos.top().second < i)
                ativos.pop();
            if(ativos.size())
                dsu.join(i, 2*ativos.top().first - i);
            if(a[i])
                ativos.push({i, i+a[i]});
        }
        ll ans = 0;
        for(int i = 0; i <= n; i++)
            if(dsu.find(i) == i)
                ans += 1ll * dsu.peso[i] * (dsu.peso[i] - 1) / 2;
        printf("%lld\n", ans);
    }
}
