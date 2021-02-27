#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename T> ostream& operator<<(ostream &os, const deque<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
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
constexpr int maxn = 5e6 + 10;
constexpr int logn = 22;
constexpr int mod = 1000000007;

int mn[maxn], mx[maxn], a[maxn];

void check_esp(const deque<int>& now) {
	int val = 0;
	for(int i = 0; i < sz(now) && i < logn; i++) {
		val += now[i] * (1 << i);
		mn[val] = min(mn[val], 0), mx[val] = max(mx[val], 0);
	}
}

void check(const deque<int>& now, int b, int primeiro) {
	for(int pos = 0; pos < sz(now) && pos <= primeiro; pos++) {
		int val = 0, teve_ligado = 0;
		for(int i = pos; i < min(logn+pos, sz(now)); i++) {
			val += now[i] * (1 << (i-pos));
			if(i >= primeiro)
				teve_ligado |= now[i];
			if(i >= primeiro && teve_ligado) {
				mn[val] = min(mn[val], b);
				mx[val] = max(mx[val], b);
			}
		}
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < maxn; i++)
		mn[i] = inf, mx[i] = -1;
	for(int j = 0; j < n; j++)
		scanf("%d", &a[j]);
	deque<int> now, valores;
	for(int j = 0; j < m; j++) {
		int x, b = 0; scanf("%d", &x);
		for(int l = 30; l >= 0; l--) {
			if((1 << l) <= x) {
				++b, now.push_front((x&(1<<l)) > 0);
				valores.push_front(l);
				check_esp(now);
			}
		}

		for(int i = 0; i < sz(now); i++)
			now[i] ^= 1, check(now, 1<<valores[i], i), now[i] ^= 1;
		while(sz(now) >= logn)
			now.pop_back();
	}
	for(int i = 0; i < n; i++)
		printf("%d %d\n", mn[a[i]]<inf?mn[a[i]]:-1, mx[a[i]]);
}
