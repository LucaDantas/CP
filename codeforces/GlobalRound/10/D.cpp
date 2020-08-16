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
#define db(...) 0
#define debug(...) 1
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

char t[] = {'L', 'R'};

void SOLVE() {
	int n; cin >> n;
	string s; cin >> s;
	bool ok = 0;
	rep(i,0,n) if(s[i] != s[(i+1)%n]) ok = 1;
	if(!ok) {printf("%d\n", (n+2)/3); return;}
	vi pares; // os pares são i e (i+1)%n
	rep(i,0,n) if(s[i] == 'R' && s[(i+1)%n] == 'L') pares.pb(i);
	int ans = 0;
	// db(pares);
	for(int i = 0; i < sz(pares); i++) {
		string here;
		for(int j = (pares[i]+2)%n; j != pares[(i+1)%sz(pares)]; j = (j+1)%n) {
			here.pb(s[j]);
		}
		if(!sz(here)) continue;
		int cntL = 0, cntR = 0;
		rep(pos,0,sz(here)) if(here[pos] == 'L') cntL++; else cntR++;
		ans += (cntR+1)/3 + (cntL+1)/3;
		// db(here);
	}
	// debug();
	printf("%d\n", ans);
	/*
	if(ok) {
		dec(i,n-1,st) {
			if(s[i] == t[type]) {
				cnt++;
			}
			else{ 
				fim = i;
				break;
			}
		}
	}
	int ans = (cnt-1)/2;
	if(ok) {
		// assert(st >= 1);
		int here = 1;
		rep(i,st+1,fim+1) {
			db(i, here);
			if(s[i] == s[i-1])
				here++;
			else
				ans += (here-1)/2, here = 1;
		}
		ans += (here-1)/2;
	}
	debug();
	printf("%d\n", ans);
	*/
}

int main() {
	fast;
	int T; cin >> T;
	while(T--) SOLVE();
}
