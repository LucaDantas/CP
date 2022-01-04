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
template<typename T> ostream& operator<<(ostream &os, const deque<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }

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
constexpr int maxn = 5e4 + 10;
constexpr int mod = 1000000007;

struct MaxQueue
{
	int t, t_rmv, lazy;
	deque<pair<int,pair<int,int>>> q;
	MaxQueue() : t(0), t_rmv(0), lazy(0) { q.clear(); }
	void push(int v, int id) {
		v -= lazy;
		while(q.size() && v > q.front().first)
			q.pop_front();
		q.push_front({v, {++t, id}});
	}
	void pop() { if(++t_rmv == q.back().second.first) q.pop_back(); }
	void add(int x) { lazy += x; }
	int query_val() { return q.size() ? q.back().first + lazy : inf; }
	int query_id() { return q.size() ? q.back().second.second : -1; }
};

signed main() {
	int t; scanf("%lld", &t);
	while(t--) {
		int n; scanf("%lld", &n);
		vi a(n), pref(n);
		
		for(int& x : a)
			scanf("%lld", &x);

		int x; scanf("%lld", &x);

		pref = a;
		for(int i = 1; i < n; i++)
			pref[i] += pref[i-1];

		MaxQueue q;
		q.push(0, 0);
		q.add(x);

		vi l(n, -1);

		// db(pref);

		for(int i = 1; i < n; i++) {
			int hm = q.query_val() + x;
			// db(i, hm);
			// db(q.q, q.la);
			do {
				if(hm > pref[i]) {
					// achei um caso q dá ruim
					l[i] = q.query_id();
					while(q.query_id() == l[i]) q.pop();
						// db("OPA");
				}
				hm = q.query_val() + x;
			} while(q.q.size() && hm > pref[i]);

			q.push(pref[i-1], i);
			q.add(x);
		}

		// db(l);

		int ans = 0, last = -1;
		for(int i = 0; i < n; i++)
			if(l[i] > last) ++ans, last = i;
		printf("%lld\n", n-ans);
	}
}
