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
		int n; scanf("%d", &n); n <<= 1;
		vector<int> a(n);
		for(int& x : a)
			scanf("%d", &x);
		sort(all(a));
		bool massa = 0;
		for(int i = 0; i < n-1; i++) {
			int val = a[n-1];
			bool ok = 1;
			multiset<int> st;
			vector<pii> pos;

			for(int x : a)
				st.insert(x);
			
			pos.pb({a[n-1], a[i]});
			
			st.erase(st.find(a[n-1]));
			st.erase(st.find(a[i]));

			while(st.size()) {
				int now = *(--st.end());
				st.erase(st.find(now));
				auto opa = st.lower_bound(val - now);
				if(opa == st.end() || now + *opa != val) {
					ok = 0;
					break;
				}
				else pos.pb({now, *opa});
				st.erase(opa);
				val = now;
			}

			if(ok) {
				puts("YES");
				printf("%d\n", a[n-1]+a[i]);
				for(pii x : pos)
					printf("%d %d\n", x.ff, x.ss);
				massa = 1; break;
			}
		}
		if(!massa)
			puts("NO");
	}
}
