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
constexpr int maxn = 1e3 + 10;
constexpr int mod = 1000000007;

int a[maxn][maxn];

void solve() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			char c; scanf(" %c", &c);
			a[i][j] = c=='a';
		}
	}
	if(m%2 == 0 && n == 2 && a[1][2] != a[2][1]) {puts("NO"); return;}
	puts("YES");
	if(m%2) {
		for(int i = 0; i < m+1; i++)
			printf("%d ", (i%2)+1);
		puts("");
		return;
	}
	if(n == 2) {
		for(int i = 0; i < m+1; i++)
			printf("%d ", (i%2)+1);
		puts("");
		return;	
	}
	if(a[1][2] == a[2][3] && a[2][3] == a[3][1]) {
		for(int i = 0; i < m+1; i++)
			printf("%d ", (i%3)+1);
		puts("");
		return;
	}
	for(int i = 1; i <= 3; i++)
		for(int j = i+1; j <= 3; j++)
			if(a[i][j] == a[j][i]) {
				for(int k = 0; k < m+1; k++)
					printf("%d ", (k%2)?i:j);
				puts("");
				return;
			}
	int center = 0;
	for(int i = 0; i < 3; i++)
		if(a[i+1][(i+1)%3+1] != a[i+1][(i+2)%3+1])
			center = i+1;
	vector<int> outro;
	for(int i : {1, 2, 3})
		if(i != center)
			outro.pb(i);
	if(m%4 == 0) {
		printf("%d ", center);
		for(int i = 0; i < m/2; i++)
			printf("%d ", i%2?center:outro[0]);
		for(int i = 0; i < m/2; i++)
			printf("%d ", i%2?center:outro[1]);
	} else {
		printf("%d ", outro[0]);
		for(int i = 0; i < m/2; i++)
			printf("%d ", i%2?outro[0]:center);
		for(int i = 0; i < m/2; i++)
			printf("%d ", i%2?center:outro[1]);
	}
	puts("");
}

int main() {
	int t; scanf("%d", &t);
	while(t--) solve();
}
