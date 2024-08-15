#include <bits/stdc++.h>
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()

constexpr int maxn = 2e7+10;

vector<int> pr;

int f[maxn];

void pre() {
    f[0] = f[1] = 1;
    for(int i = 2; i < maxn; i++) {
        if(!f[i]) pr.push_back(i), f[i] = i;
        for(int j = 0; j < sz(pr) && pr[j] <= f[i] && i * pr[j] < maxn; j++)
            f[i * pr[j]] = pr[j];
    }
}

set<pair<int,int>> dp;

int n, m, va, vb;
long long ans;

inline long long V(int i, int j) {
    return j <= n ? 1ll * max(i, j) * max(va, vb) + 1ll * min(i, j) * min(va, vb) : 1ll * i * va + 1ll * j * vb;
}

bool flg = 0;

void solve(int a, int b) {
    if(dp.count({a, b}))
        return;
    if(b == m) flg=1;
    ans = max(ans, V(a,b));
    dp.insert({a, b});
    if(__gcd(a+1, b) == 1 && a+1 <= n)
        solve(a+1, b);
    if(__gcd(a, b+1) == 1 && b+1 <= m)
        solve(a, b+1);
}

int main() {
    pre();
    int t; scanf("%d", &t);

    while(t--) {
        scanf("%d %d %d %d", &n, &m, &va, &vb);

        int p = *prev(upper_bound(all(pr), m));

        for(int q = min(n, p-1); !flg; q--)
            solve(q, p);

        printf("%lld\n", ans);

        dp.clear();
        ans = 0;
        flg = 0;
    }
}
