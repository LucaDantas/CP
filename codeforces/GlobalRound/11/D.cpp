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
constexpr int maxn = 100;
constexpr int mod = 1000000007;

struct DSU
{
	// o primeiro item do grupo vai ser o pai
	int pai[maxn], back[maxn];
	DSU() {
		for(int i = 0; i < maxn; i++)
			pai[i] = back[i] = i;
	}
	int find(int x) {
		return pai[x]==x?x:pai[x]=find(pai[x]);
	}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) assert(0);
		if(a > b)
			swap(a, b);
		back[a] = back[b];
		pai[b] = a;
	}
} dsu;

vector<int> a;

vector<vector<int>> ans;

void op(int p1, int p2, int p3) {
	int n = sz(a);
	vector<int> s[4];
	int pos = 0, oto = 0;
	for(int i = 0; i < p1; i++, pos++)
		s[0].pb(a[pos]);
	for(int i = 0; i < p2; i++, pos++)
		s[1].pb(a[pos]);
	for(int i = 0; i < p3; i++, pos++)
		s[2].pb(a[pos]);
	for(; pos < n; pos++, oto++)
		s[3].pb(a[pos]);
	swap(s[1], s[2]);
	swap(s[0], s[3]);
	a.clear();
	for(int i = 0; i < 4; i++)
		for(auto it : s[i])
			a.pb(it);
	vector<int> here;
	for(auto x : {p1, p2, p3, oto})
		if(x) here.pb(x);
	ans.pb(here);
}

int pos[maxn];

int main() {
	int n; scanf("%d", &n);
	a.resize(n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	while(!is_sorted(all(a))) {
		clr(pos, -1);
		for(int i = 0; i < n; i++) {
			if(a[i] != dsu.find(a[i]))
				continue;
			if(pos[dsu.back[a[i]]+1] != -1) {
				int val = a[i];
				op(pos[dsu.back[a[i]]+1], i - pos[dsu.back[a[i]]+1], 
					dsu.back[a[i]] - a[i] + 1); // depois completa até o fim
				dsu.join(val, dsu.back[val]+1);
				break;
			} else pos[a[i]] = i;
		}
	}

	printf("%d\n", sz(ans));
	for(auto it : ans) {
		printf("%d ", sz(it));
		for(auto x : it)
			printf("%d ", x);
		printf("\n");
	}
}
