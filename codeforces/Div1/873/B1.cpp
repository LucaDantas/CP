#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vi a(n+2), suf(n+2);
        a[0] = inf;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        a[n+1] = -inf;
        ll total = 0, salvo = 0;
        for(int sz = 1; sz <= n; sz++)
            total += 1ll * (sz-1) * (n-sz+1);
        for(int centro = 1; centro < n; centro++) { // divisao a direita de centro
            suf[centro] = inf;
            for(int i = centro+1; i <= n; i++)
                suf[i] = min(suf[i-1], a[i]);
            int mx = -inf;
            for(int i = centro, ptr = n; i >= 1; i--) {
                mx = max(mx, a[i]);
                while(suf[ptr] < mx)
                    --ptr;
                salvo += ptr - centro; // quantos finais validos tem pra essa pos
            }
        }
        printf("%lld\n", total - salvo);
    }
}
