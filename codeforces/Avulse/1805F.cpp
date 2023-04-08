#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9+7, inf = 0x3f3f3f3f, maxsz = 64;

bool check(vector<int>& a, int val, int sz) {
    int n = (int)(a.size());
    int gut = 0;
    for(int i = n-2, ptr = 0; i >= 0; i--) {
        if(a[i] + a[i+1] <= val) {
            ptr = max(ptr, i+1);
            for(; ptr < n && a[i] + a[ptr] <= val; ptr++);
            gut += ptr - i - 1; // ptr eh o primeiro fora do intervalo valido
        }
        if(gut >= sz) return 1;
    }
    return 0;
}

void build(vector<int>& a, int val, int sz) {
    int n = (int)(a.size());
    vector<int> aux;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n && a[i] + a[j] < val; j++)
            aux.push_back(a[i] + a[j]);
    sort(aux.begin(), aux.end());
    while((int)aux.size() < sz)
        aux.push_back(val);
    a = aux;
}

int main() {
    int n; scanf("%d", &n);
    vector<int> a(n);
    for(int& x : a)
        scanf("%d", &x);

    sort(a.begin(), a.end());
    while(a.size() > maxsz)
        a.pop_back();

    int base = 0;

    for(int i = n; i > 1; i--) {
        int l = 0, r = 2*inf;
        int ans = 0;
        while(l <= r) {
            int m = l + ((r-l) >> 1);
            if(check(a, m, min(maxsz, i-1)))
                ans = m, r = m-1;
            else
                l = m+1;
        }
        build(a, ans, min(maxsz, i-1));

        int norm = a[0];
        base = (2*base + norm) % mod; // eu tenho que duplicar a base porque ela ta aparecendo duas vezes quando eu faco a uniao
        for(int& x : a)
            x -= norm;
    }
    printf("%d\n", (a[0] + base) % mod);
}

