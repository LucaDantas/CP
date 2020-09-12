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

#define int long long

int a[maxn], dif[maxn];

ll solve(ll ct, ll ini) {
    // solve for x + y = ini
    // while max(x, y + ct) must be the smallest possible
    // I think it implies that x - y - ct <= 1
    ll l = -(ll)1e18L, r = (ll)1e18L;
    ll best = (ll)1e18L;
    while(l <= r) {
        ll mid = l + ((r-l) >> 1);
        ll p1 = max(mid, ini - mid + ct);
        ll p2 = max(mid+1, ini - mid - 1 + ct);
        if(p1 <= p2) {
            best = min(best, p1);
            r = mid-1;
        } else {
            best = min(best, p2);
            l = mid+1;
        }
    }
    return best;
}

int32_t main() {
    fast;
	int n; cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++)
        dif[i] = a[i+1] - a[i];
    // a gente quer achar o minimo para max(x, y + constante), com x+y = inicio
    // onde essa constante é a soma dos valores positivos da diferença
    ll ct = 0, ini = a[1];
    for(int i = 1; i < n; i++)
        if(dif[i] > 0) ct += dif[i];

    // cout << ct << ' ' << ini << '\n';
    cout << solve(ct, ini) << '\n';

    int q; cin >> q;
    while(q--) {
        int l, r, x;
        cin >> l >> r >> x;
        if(l == 1) {
            ini += x;
        } else {
            if(dif[l-1] > 0) ct -= dif[l-1];
            dif[l-1] += x;
            if(dif[l-1] > 0) ct += dif[l-1];
        }
        if(r != n) {
            if(dif[r] > 0) ct -= dif[r];
            dif[r] -= x;
            if(dif[r] > 0) ct += dif[r];
        }
        // cout << ct << ' ' << ini << '\n';
        cout << solve(ct, ini) << '\n';
    }
}
