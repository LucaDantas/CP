#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int n, p, q, s;
int a[maxn], b[maxn];

bool check(int val) {
    int qtd = 0;
    static multiset<int> st; st.clear();
    for(int i = 0; i < q; i++)
        st.insert(b[i]);
    for(int i = 0; i < p && st.size(); i++) {
        if(a[i] > s) continue;
        int maior = min(s - a[i], a[i] + val);
        auto it = st.lower_bound(maior);
        if(it != st.end() && a[i] + *it <= s && abs(*it - a[i]) <= val)
            ++qtd, st.erase(it);
        else if(it != st.begin() && abs(a[i] - *prev(it)) <= val)
            ++qtd, st.erase(prev(it));
    }
    return qtd >= n;
}

int main() {
    scanf("%d %d %d %d", &n, &p, &q, &s);
    for(int i = 0; i < p; i++)
        scanf("%d", a+i);
    for(int i = 0; i < q; i++)
        scanf("%d", b+i);
    sort(a, a+p, greater<int>());

    int l = 0, r = s, ans = -1;
    while(l <= r) {
        int m = (l+r) >> 1;
        if(check(m))
            ans = m, r = m-1;
        else
            l = m+1;
    }
    printf("%d\n", ans);
}