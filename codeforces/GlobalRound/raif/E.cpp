#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll, int>;
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

inline ll sq(int x) {return 1ll*x*x;}

vector<int> a, dv;

inline ll calc(int i) {return 1ll * (dv[i] - (a[i]%dv[i])) * sq(a[i]/dv[i])
			+ 1ll * (a[i]%dv[i]) * sq((a[i]+dv[i]-1)/dv[i]);}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	a.resize(n); dv.assign(n, 1);
	priority_queue<pii> q;
	int cnt = 0;
	for(int& x : a) {
		scanf("%d", &x);
		dv[cnt]++;
		ll sv = calc(cnt);
		dv[cnt]--;
		q.push({calc(cnt) - sv, cnt});
		cnt++;
	}
	for(cnt = n; cnt < k; cnt++) {
		int id = q.top().ss; q.pop();
		dv[id]++;
		dv[id]++;
		ll sv = calc(id);
		dv[id]--;
		q.push({calc(id) - sv, id});
	}
	ll ans = 0;
	for(int i = 0; i < n; i++)
		ans += calc(i);
	printf("%lld\n", ans);
}
