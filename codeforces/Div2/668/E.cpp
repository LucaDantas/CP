#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

#define pb push_back

constexpr int maxn = 3e5+10;

int a[maxn], ans[maxn], bit[maxn];

vector<pii> Q[maxn];

void upd(int x, int v) {
    for(x++; x < maxn; x += x&-x)
        bit[x] += v;
}

int query(int x) {
    int ret = 0;
    for(x++; x > 0; x -= x&-x)
        ret += bit[x];
    return ret;
}

int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]), a[i] = i - a[i];
    for(int i = 1; i <= q; i++) {
        int l, r; scanf("%d %d", &l, &r);
        Q[n-r].pb({l, i});
    }
    
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) // se eu sou 0, não importa quem veio antes vai crescer em 1 (menos o caso de tirando todo mundo)
            upd(0, 1), upd(i, -1);
        else if(a[i] > 0) {
            // then we binary search to find the last item that has the value I need
            int l = 0, r = i-1, best = -1;
            while(l <= r) {
                int mid = (l+r) >> 1;
                if(query(mid) >= a[i]) {
                    best = mid, l = mid+1;
                } else {
                    r = mid-1;
                }
            }
            if(best >= 0)
                upd(0, 1), upd(best+1, -1);
        }
        
        for(auto x : Q[i])
            ans[x.second] = query(x.first);
    }
    for(int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
}