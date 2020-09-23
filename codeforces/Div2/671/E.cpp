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

vi pr;
vector<pii> decomp;

bool f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++)
		if(!f[i])
			for(int j = i+i; j < maxn; j += i)
				f[j] = i;
	for(int i = 2; i < maxn; i++)
		if(!f[i])
			pr.pb(i);
}

vector<int> gone;

void so(int p) {
	for(int v = decomp[p].ff, cnt = 1; cnt <= decomp[p].ss; cnt++, v *= decomp[p].ff)
		gone.pb(v);
}

void comb(int p) {
	int n = sz(gone);
	bool ok = 0;
	for(int v = decomp[p].ff, cnt = 1; cnt <= decomp[p].ss; cnt++, v *= decomp[p].ff) {
		for(int i = n-1; i >= 0; i--) {
			gone.pb(gone[i]*v);
			if(!ok) {
				so(p);
				ok = 1;
			}
		}
	}
}


int main() {
	sieve();
	int t; scanf("%d", &t);
	while(t--) {
		decomp.clear();
		gone.clear();
		
		int n; scanf("%d", &n);
		for(int i = 0; i < sz(pr); i++) {
			if(!(n%pr[i])) decomp.eb(pr[i], 0);
			while((n%pr[i]) == 0)
				n /= pr[i], decomp.back().ss++;
		}
		if(n>1) decomp.eb(n, 1);

		int ans = 0;
		bool tudo1 = 1;
		for(int i = 0; i < sz(decomp); i++)
			if(decomp[i].ss != 1) tudo1 = 0;
		if(sz(decomp) == 2 && tudo1) ans = 1;

		n = sz(decomp);

		so(0);
		for(int i = 1; i < n; i++)
			comb(i);

		for(auto it : gone)
			printf("%d ", it);
		printf("\n%d\n", ans);
	}
}