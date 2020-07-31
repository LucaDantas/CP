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
void debug() { cerr << '\n'; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...); }
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
	fast;
	int T; cin >> T;
	while(T--) {
		ll n, k; cin >> n >> k;
		pii a, b; cin >> a.ff >> a.ss >> b.ff >> b.ss;
		if(a.ff > b.ff) swap(a, b);
		ll bridge, have, area;
		if(b.ff > a.ss) {
			bridge = b.ff - a.ss;
			have = 0;
		} else 	{
			bridge = 0;
			have = min(a.ss, b.ss) - b.ff;
		}
		
		area = a.ss-a.ff+b.ss-b.ff-2*have;
		k -= n*have;

		if(k <= 0) {
			cout << "0\n"; continue;
		}

		if(area + bridge == 0) {
			cout << 2*k << '\n'; continue;
		}

		ll precisa = k / (area+bridge);

		precisa = min(n, precisa);

		ll cost = precisa * (area + 2*bridge);

		k -= precisa * (area + bridge);

		if(precisa == n) {
			cost += 2*k;
		} else {
			if(precisa >= 1)
				cost += min(2*k, bridge + k);
			else
				cost += bridge + k;
		}

		cout << cost << '\n';
	}
}
