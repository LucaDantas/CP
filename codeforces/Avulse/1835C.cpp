#include <bits/stdc++.h>
using namespace std;

mt19937 rng(random_device{}());

int rnd(int x) { return (int)(rng() % x + x) % x; }
int rnd(int l, int r) { return rnd(r-l) + l; } // exclusive

array<int,4> get_ans(pair<int,int> p1, pair<int,int> p2) {
    if(p1 > p2)
        swap(p1, p2);
    // printf("vapo %d %d | %d %d\n", p1.first, p1.second, p2.first, p2.second);
    auto [l1, r1] = p1;
    auto [l2, r2] = p2;
    if(l1 == l2) return {r1+1, r1+1, r1+2, r2};
    else if(r1 == r2) return {l1, l2-2, l2-1, l2-1};
    else if(r1 < l2) return {l1, r1, l2, r2};
    else if(r1 < r2) return {l1, l2-1, r1+1, r2};
    else return {l1, l2-1, r2+1, r1};
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int k; scanf("%d", &k);

        vector<long long> a((1<<(k+1))+1);
        map<long long, int> seen;
        map<long long, pair<int,int>> seen2;
        array<int,4> ans = {-1, -1, -1, -1};

        for(int i = 1; i < (int)(a.size()); i++) {
            scanf("%lld", &a[i]);
            if(seen.count(a[i]))
                ans = {seen[a[i]], seen[a[i]], i, i};
            seen[a[i]] = i;
        }

        int lixo = seen.count(0) ? seen[0] : 0x3f3f3f3f;

        if(ans[0] != -1) { printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]); continue; }

        for(int i = 1; i < (int)(a.size()); i++)
            a[i] ^= a[i-1];

        while(true) {
            auto gen = [&]() -> pair<int,int> { auto [x, y] = pair<int,int>(rnd(1, (int)(a.size())), rnd(1, (int)(a.size()))); return {min(x, y), max(x,y)}; };
            auto [l, r] = gen();
            while(l == lixo || r == lixo)
                tie(l, r) = gen();
            // printf("gerei %d %d | %lld\n", l, r, a[r] ^ a[l-1]);
            if(seen2.count(a[r] ^ a[l-1]) && seen2[a[r] ^ a[l-1]] != pair<int,int>(l, r)) {
                ans = get_ans(seen2[a[r] ^ a[l-1]], pair<int,int>(l, r));
                break;
            }
            seen2[a[r] ^ a[l-1]] = {l, r};
        }
        printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
    }
}
