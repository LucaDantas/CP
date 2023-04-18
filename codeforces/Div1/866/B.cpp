#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int n;

struct Rec {
    int r, c, id;
    bool operator<(const Rec& o) { return r < o.r; }
    bool operator>(const Rec& o) { return c < o.c; }
};

bool mark[maxn];

bool go(vector<Rec> a, vector<Rec> b, long long szr, long long szc) {
    for(int i = 0; i <= n; i++)
        mark[i] = 0;
    
    int last = -1;
    while(a.size() + b.size() != last) {
        last = a.size() + b.size();
        while(a.size() && (mark[a.back().id] || a.back().r == szr)) {
            if(mark[a.back().id]) {
                a.pop_back();
                continue;
            }

            szc -= a.back().c;
            mark[a.back().id] = 1;
            a.pop_back();
        }

        while(b.size() && (mark[b.back().id] || b.back().c == szc)) {
            if(mark[b.back().id]) {
                b.pop_back();
                continue;
            }

            szr -= b.back().r;
            mark[b.back().id] = 1;
            b.pop_back();
        }
    }

    return last == 0; // did I manage to fit everyone?
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        vector<Rec> a(n), b;
        int cnt = 0;
        long long sz = 0;
        for(auto &[r, c, id] : a)
            scanf("%d %d", &r, &c), id = cnt++, sz += 1ll * r * c;
        b = a;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), greater<>());
        vector<pair<long long, long long>> ans;

        {
            long long szr = a.back().r, szc = sz / szr;
            if(!(sz % szr) && go(a, b, szr, szc))
                ans.push_back({szr, szc});
        }

        {
            long long szc = b.back().c, szr = sz / szc;
            if(!(sz % szc) && a.back().r != sz / szc && go(a, b, szr, szc))
                ans.push_back({szr, szc});
        }

        printf("%ld\n", ans.size());
        for(auto [x, y] : ans)
            printf("%lld %lld\n", x, y);
    }
}
