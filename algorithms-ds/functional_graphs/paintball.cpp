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
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << " " << I; debug(F...); }
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") ==", debug(__VA_ARGS__)
#define jump cerr << endl
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
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;

int f[maxn], fam[maxn], sz[maxn], qtd_src[maxn], mark[maxn], grau[maxn], cc, n;

vi sources;

void dfs(int u) {
	int v = f[u];
	grau[v]++;
	mark[u] = 1;

	if(mark[v] == 1) {
		fam[u] = cc++;
	}
	else if(!mark[v]) {
		dfs(v);
		fam[u] = fam[v];
	}
	else fam[u] = fam[v];

	mark[u] = 2;
	sz[fam[u]]++;
}

int get_max() {
	int ans = 0;
	rep(i,0,cc) {
		if(!qtd_src[i]) { 
			if(sz[i] > 1)
				ans += sz[i]-1;
			else ans++;
		}
		else {
			ans += sz[i] - qtd_src[i];
		}
	}
	return ans;
}

int get_min() {
	clr(mark, 0); // set everyone to alive, then kill with bfs
	queue<int> q;
	for(auto u : sources)
		q.push(u);

	int ans = 0;

	while(q.size()) {
		int u = q.front(); q.pop();
		sz[fam[u]]--; mark[u] = 1;
		if(mark[f[u]]) continue;
		
		ans++;
		mark[f[u]] = 1;
		sz[fam[u]]--;

		grau[f[f[u]]]--;
		if(!grau[f[f[u]]])
			q.push(f[f[u]]);
	}

	rep(i,0,cc) ans += (sz[i]+1)/2;
	return ans;
}

int main() {
	fast;
	
	freopen("paintball.in", "r", stdin);
	freopen("paintball.out", "w", stdout);

	cin >> n;
	
	int nxt;
	rep(i,0,n) cin >> nxt, f[i] = nxt-1;
	
	rep(i,0,n) if(!mark[i]) dfs(i);
	
	rep(i,0,n) if(!grau[i]) qtd_src[fam[i]]++, sources.eb(i);

	int mx = get_max();

	cout << get_min() << ' ' << mx << '\n';
}
