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

int comp[maxn], ans[maxn], pot[maxn][2];
bool mark[maxn];

int p;
int nxt(int i, int a) { return (int)(1ll * i * a % p); }

int main() {
	int a, b; scanf("%d %d %d", &p, &a, &b);
	if(a < b) swap(a, b);
	int n = 0, m = 0, v = 1;
	do {
		++n; v = nxt(v, a);
		mark[v] = 1;
	} while(v != 1);
	do {
		++m; v = nxt(v, b);
	} while(!mark[v]);
	if(p-1 != n*m) return puts("No"), 0;
	puts("Yes");
	if(m == 1) {
		v = 1;
		do {
			printf("%d ", v);
			++n; v = nxt(v, a);
		} while(v != 1);
		puts("1");
	} else {
		pot[0][0] = pot[0][1] = 1;
		for(int i = 1; i <= p; i++) pot[i][0] = nxt(pot[i-1][0], a), pot[i][1] = nxt(pot[i-1][1], b);
		if(n&1) {
			for(int j = 0; j < m; j++)
				if(j&1) for(int i = n-2; i >= 0; i--) printf("%d ", (int)(1ll * pot[i][0] * pot[j][1] % p));
				else for(int i = 0; i < n-1; i++) printf("%d ", (int)(1ll * pot[i][0] * pot[j][1] % p));
			for(int j = m-1; j >= 0; j--) printf("%d ", (int)(1ll * pot[n-1][0] * pot[j][1] % p));
		} else {
			for(int i = 1; i <= n; i++)
				for(int j = (i&1)?0:m-1; j < m && j >= 0; j += (i&1)?1:-1)
					printf("%d ", (int)(1ll * pot[i-1][0] * pot[j][1] % p));
		}
		puts("1");
	}
}
