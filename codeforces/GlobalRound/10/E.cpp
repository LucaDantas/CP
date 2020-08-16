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

int val[25][25];

int main() {
	fast;
	int n; cin >> n;
	for(int i = 0; i < n; i+=2) {
		for(int j = 0; j < n; j++) {
			val[i][j] = i+j;
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			if(i%2==0)
				cout << (1ll << val[i][j]) << ' ';
			else cout << "0 ";
		cout << '\n';
	}
	cout << flush;
	int q; cin >> q;
	while(q--) {
		ll k; cin >> k;
		cout << "1 1\n";
		int col = 1, lin = 1, last = 1;
		for(int i = 1; i < 2*n-1; i++) {
			int now = ((1ll << i)&k) > 0;
			if(now == last) col++;
			else lin++;
			last = now;
			cout << lin << ' ' << col << '\n';
		}
		cout << flush;
	}
}
