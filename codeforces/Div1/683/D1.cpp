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
constexpr int maxn = 2e5 + 10;
constexpr int mod = 1000000007;

int cnt[maxn], livre[maxn];

vector<pii> seq[maxn];

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n), ultimos, last(n+1, -1), dps(n, -1);
	int qtd = 0, top = -1;
	for(int& x : a) {
		scanf("%d", &x);
		cnt[x]++;
		if(cnt[x] > qtd)
			qtd = cnt[x], top = x;
	}
	int last1 = 0;
	for(int i = 0; i < n; i++) {
		if(a[i] == top) {
			for(int j = 1; j <= min(n, 100); j++)
				if(cnt[j] && j != top)
					seq[j].pb({-1, i});
		} else {
			seq[a[i]].pb({1, i});

		}
	}
	int ans = 0;
	for(int i = 1; i <= min(100, n); i++) {
		if(!sz(seq[i])) continue;
		int menor = 0, maior = 0, now = 0;
		for(pii x : seq[i])
			now += x.ff, menor = min(menor, now), maior = max(maior, now);
		menor -= 2*menor;
		vector<int> pref(menor + maior + 1, -1);
		bool ok = 0;
		for(int j = 0; j <= cnt[i]; j++)
			if(seq[i][j].ff == 1)
				ok = 1;
		pref[menor] = ok?0:seq[i][0].ss+1;
		now = 0;
		for(int j = 0; j < sz(seq[i]); j++) {
			pii x = seq[i][j];
			now += x.ff;
			if(pref[now+menor] == -1)
				pref[now+menor] = seq[i][j].ss+1;
			else {
				int fim = j+1 < sz(seq[i])?seq[i][j+1].ss-1:n-1;
				ans = max(ans, fim - pref[now+menor] + 1);
			}
		}
	}
	printf("%d\n", ans);
}
