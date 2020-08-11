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
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
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

int pot[20][20];

int main() {
	fast;
	int n; cin >> n;
	ll ans = 0;
	rep(i,0,n) {
		string massa; cin >> massa;
		int t = sz(massa);

		int antes = 0, dec = 0;
		bool ok = 0;
		rep(j,0,t) {
			if(massa[j] == '.') ok = 1; 
			else if(ok) dec++;
			else antes++;
		}

		ll a = 0;

		rep(j,0,t)
			if(massa[j] != '.')
				a *= 10ll, a += massa[j] - '0';
		
		rep(j,dec,9) a *= 10ll;

		int p2 = 0, p5 = 0;
		while(a%2==0) a/=2ll, p2++;
		while(a%5==0) a/=5ll, p5++;

		p2 = min(p2, 18);
		p5 = min(p5, 18);

		rep(j,18-p2,19)
			rep(x, 18-p5, 19)
				ans += pot[j][x];

		pot[p2][p5]++;
	}

	cout << ans << '\n';
}
