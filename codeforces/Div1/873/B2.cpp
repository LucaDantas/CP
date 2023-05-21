#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 3e5 + 10;
constexpr int logn = 20;
constexpr int mod = 1000000007;

struct ST {
    vector<vector<int>> mx;
    ST(const vector<int>& a) : mx(logn, vector<int>(sz(a))) {
        for(int i = 0; i < sz(a); i++)
            mx[0][i] = a[i];
        for(int l = 1; l < logn; l++)
            for(int i = 0; i < sz(a); i++)
                mx[l][i] = max(mx[l-1][i], (i + (1<<(l-1)) < sz(a)) ? mx[l-1][i + (1<<(l-1))] : 0);
    }
    int query(int x, int v) {
        // ultimo elemento a esquerda de x maior q v
        for(int l = logn-1; l >= 0; l--)
            if(x >= (1<<l) && mx[l][x - (1<<l)] < v)
                x -= 1<<l;
        return x-1;
    }
};

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vi a(n+2), suf(n+2);
        a[0] = inf;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        a[n+1] = -inf;
        ST st(a);
        ll ans = 0;
        for(int sz = 1; sz <= n; sz++)
            ans += 1ll * (sz-1) * (n-sz+1);
        vi l(n+2), r(n+2);
        for(int i = 1; i <= n; i++) {
            l[i] = i-1;
            while(l[i] && a[i] < a[l[i]])
                l[i] = l[l[i]];
        }
        for(int i = n; i >= 1; i--) {
            r[i] = i+1;
            while(a[i] < a[r[i]])
                r[i] = r[r[i]];
        }
        for(int i = 1; i <= n; i++)
            ans -= 1ll * (l[i] - st.query(l[i]+1, a[i])) * (r[i] - i);
        printf("%lld\n", ans);
    }
}
