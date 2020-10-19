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

constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;

int32_t main() {
	fast;
	int t; cin >> t;
	while(t--) {
		int n, k; cin >> n >> k;
		string s; cin >> s;
		int first = inf, last = inf, cnt = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'W') {
				first = i-1;
				break;
			}
		}
		for(int i = n-1; i >= 0; i--) {
			if(s[i] == 'W') {
				last = i+1;
				break;
			}
		}

		if(first == inf) {
			cout << max(0ll, 2*k-1) << '\n';
			continue;
		}


		vector<int> interval;
		for(int i = first+1; i < last; i++) {
			if(s[i] == 'L')
				cnt++;
			else if(cnt > 0)
				interval.pb(cnt), cnt = 0;
		}
		
		first++;
		last = n - last;

		ll ans = 0;
		sort(all(interval));
		for(auto itv : interval) {
			db(itv);			
			if(k < itv)
				{ans += 2*k, k = 0; break;}
			else
				ans += 2*itv + 1, k -= itv;
		}
		db(first, last);
		if(k > 0) {
			if(first >= 0) {
				first = min(first, k);
				ans += 2*first;
				k -= first;
			}
			if(last >= 0) {
				last = min(last, k);
				ans += 2*last;
				k -= last+1;
			}
		}

		if(s[0] == 'W')
			ans++;

		for(int i = 1; i < n; i++) {
			if(s[i] == 'W')
				ans += 1 + (s[i-1]=='W');
		}
		cout << ans << '\n';
	}
}
