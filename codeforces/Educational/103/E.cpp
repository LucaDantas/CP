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

int ingrau[maxn];
vector<int> g[maxn];

vector<int> topBFS(int n){
	vector<int> ans;
	
	queue<int> q;
	
	for(int i = 1; i <= n; i++)
		if(ingrau[i] == 0) q.push(i);
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		ans.push_back(u);
		
		for(int v : g[u]){
			ingrau[v]--;
			if(!ingrau[v]) q.push(v);
		}
	}
	return ans;
}

string pt[maxn];

void min_self(int& a, int b) {a = min(a, b);}

int ptr;

map<string, int> mp;

int main() {
	fast;
	int n, m, k; cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) {
		cin >> pt[i];
		mp[pt[i]] = ++ptr;
	}
	for(int i = 0; i < m; i++) {
		string s; cin >> s;
		int t; cin >> t;
		bool ok = 0;
		for(int mask = 0; mask < (1 << k); mask++) {
			string l = "";
			for(int j = 0; j < k; j++)
				if(mask&(1<<j)) l.pb('_');
				else l.pb(s[j]);
			if(l == pt[t]) ok = 1;
		
		}
		if(!ok) {cout << "NO\n"; return 0;}
		for(int mask = 0; mask < (1 << k); mask++) {
			string l = "";
			for(int j = 0; j < k; j++)
				if(mask&(1<<j)) l.pb('_');
				else l.pb(s[j]);
			if(l != pt[t] && mp.count(l))
				g[mp[pt[t]]].pb(mp[l]), ingrau[mp[l]]++;
		}
	}

	vector<int> ans = topBFS(ptr);
	if(sz(ans) != n) {cout << "NO\n"; return 0;}
	cout << "YES\n";
	for(int x : ans)
		cout << x << ' ';
	cout << '\n';
}
