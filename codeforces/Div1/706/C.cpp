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

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, m; scanf("%d %d", &n, &m);
		vector<vector<char>> a(n, vector<char>(m));
		vector<int> antes(n+1), liga(n+1);
		liga[0] = 1;
		for(int i = 3; i <= n; i += 3)
			liga[i] = 1, antes[i-1] = 1;
		if(antes[n-1]) {
			fill(all(liga), 0);
			fill(all(antes), 0);
			liga[1] = 1;
			for(int i = 4; i <= n; i += 3)
				liga[i] = antes[i-1] = 1;
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				scanf(" %c", &a[i][j]);
				if(liga[i]) a[i][j] = 'X';
			}
			if(antes[i]) {
				if((a[i-1][1] == 'X' || a[i][1] == 'X'))
					a[i-1][1] = a[i][1] = 'X';
				else a[i-1][0] = a[i][0] = 'X'; 
			}
		}
		if(n == 1 || m == 1) {
			// printf("%d %d\n", n, m);
			for(auto x : a) {
				for(char c : x)
					printf("%c", 'X');
				printf("\n");
			}
			continue;
		}
		// printf("%d %d\n", n, m);
		for(auto x : a) {
			for(char c : x)
				printf("%c", c);
			printf("\n");
		}
	}
}
