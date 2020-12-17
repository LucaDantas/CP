#include <bits/stdc++.h>
using namespace std;
#define int long long
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

constexpr int inf = 0x7f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int32_t main() {
	int T; scanf("%lld", &T);
	while(T--) {
		int n, ans = 0; scanf("%lld", &n);
		vector<pii> a(n+1);
		for(int i = 0; i < n; i++)
			scanf("%lld %lld", &a[i].ff, &a[i].ss);
		a[n] = {inf, inf};
		int prox_pos = 0, pos = 0, tempo = 0, last_t = 0;
		for(int i = 0; i < n; i++) {
			int t = a[i].ff, x = a[i].ss;
			tempo -= t - last_t; // last_t = t;
			int lado = prox_pos>pos?1:-1;
			pos += lado * (t - last_t);
			if(tempo <= 0) {
				pos = prox_pos; prox_pos = x, lado = prox_pos>pos?1:-1;
				tempo = abs(x - pos);
				// db(a[i], "MUDOU");
				// if(i == n-1) {++ans, db(a[i], "ANS"); break;}
			}
			// db(a[i], pos, lado, last_t);
			// if(i == n-1) {if(lado == ); break;}
			if(lado == 1 && x >= pos && x <= prox_pos && x - pos <= a[i+1].ff - a[i].ff) ++ans/*, db(a[i], "ANS")*/;
			else if(lado == -1 && x <= pos && x >= prox_pos && pos - x <= a[i+1].ff - a[i].ff) ++ans/*, db(a[i], "ANS")*/;
			last_t = t;
		}
		printf("%lld\n", ans);
	}
}
