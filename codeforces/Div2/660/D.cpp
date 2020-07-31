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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int n;
int f[maxn], grau[maxn], chega[maxn];
ll a[maxn];

vi ord;

vi good, bad;

void top_sort() {
	queue<int> q;
	rep(i,1,n+1) if(!grau[i]) q.push(i);
	while(q.size()) {
		int u = q.front(); ord.pb(u);
		q.pop();

		int v = f[u]; if(v == -1) continue;
		grau[v]--;
		if(!grau[v]) q.push(v);
	}
}

int main() {
	scanf("%d", &n);
	rep(i,1,n+1) scanf("%lld", &a[i]);
	rep(i,1,n+1) scanf("%d", &f[i]);
	rep(i,1,n+1) if(f[i] != -1) grau[f[i]]++;
	top_sort();
	
	ll sum = 0;
	for(auto u : ord) {
		int v = f[u];
		if(v != -1) a[v] += max(0ll, a[u]);
		if(a[u] >= 0)
			good.pb(u);
		else
			bad.pb(u);
		sum += a[u];
	}
	reverse(all(bad));
	printf("%lld\n", sum);
	for(auto it : good) printf("%d ", it);
	for(auto it : bad) printf("%d ", it);
	printf("\n");
}
