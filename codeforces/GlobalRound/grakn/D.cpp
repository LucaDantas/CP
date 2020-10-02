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
constexpr int maxn = 1e6 + 10;
constexpr int mod = 1000000007;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<pii> a(n), b(m);
	for(auto& it : a)
		scanf("%d %d", &it.ff, &it.ss);
	for(auto& it : b)
		scanf("%d %d", &it.ff, &it.ss);

	vector<pii> talvez;

	for(int i = 0; i < n; i++) {
		for(auto it : b) {
			if(a[i].ss > it.ss || a[i].ff > it.ff) continue;
			talvez.pb({it.ff - a[i].ff+1, it.ss - a[i].ss+1});
		}
	}

	if(!sz(talvez)) {puts("0"); return 0;}

	sort(all(talvez));

	int maior = 0, ans = inf;
	reverse(all(talvez));

	for(auto& it : talvez) {
		ans = min(ans, it.ff + maior);
		maior = max(maior, it.ss);
		swap(it.ff, it.ss);
	}

	maior = 0;
	sort(all(talvez));
	reverse(all(talvez));

	for(auto& it : talvez) {
		ans = min(ans, it.ff + maior);
		maior = max(maior, it.ss);
	}

	printf("%d\n", ans);
}