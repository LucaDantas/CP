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
constexpr int maxn = 1e5 + 10;
constexpr int mod = 1000000007;
constexpr double eps = 1e-6;

// we know that all the number will be a linear combination of the initial value
// plus a constant that depends on the edges

// if we get to a node that has already been counted we need to see three cases
// if a[i] == a[j] && b[i] == b[j], just ignore. if a[i] == a[j] && b[i] != b[j]
// we have a contradiction and we say it is not possible. if a[i] != a[j], then
// a[i] * a[j] == -1, because if one of them is zero we have a contradiction
// having that we can find the value of everyone by calculating the possible value
// of a. Let WLOG a[i] == 1 && a[j] == -1
// 1a + b[i] == b[j] - 1a -> 2a == b[j] - b[i] -> a == (b[j] - b[i])/2

// a[i] * x + b[i] == a[j] * x + b[j] -> (a[i] - a[j]) * x == b[j] - b[i]
// -> x == (b[j] - b[i]) / (a[i] - a[j])

// if there were no fixed value set we need to find the best, and that is the sum
// of absolute values, which means that if the value we choose for the variable is
// too small we'll have a big answer because we'll have large negative values
// on the other hand if the variable is too big we'll have large positive numbers
// we can use ternary search here because if we start from a large value in such
// a way that everyone is positive when we get to the n/2-th we'll stop the curve
// from going down and start getting up because there'll be more values that are
// growing instead of those that are decreasing. Since it is exactly in the middle
// we can simply find the median with median of medians of quickselect but ternary
// search is easier to code

vector<pii> g[maxn];
vi fam[maxn];

int a[maxn], b[maxn], mark[maxn], aux;
double var;

void dfs(int u) {
	fam[aux].pb(u);
	mark[u] = 1;
	for(auto pp : g[u]) {
		int v = pp.ff, c = pp.ss;
		int nxt_a = -a[u], nxt_b = c-b[u];
		if(mark[v]) {
			if(nxt_a == a[v]) {
				if(nxt_b != b[v]) {puts("NO"); exit(0);}
			}
			else {
				double pos = (double)(b[v] - nxt_b) / (double)(nxt_a - a[v]);
				if(fabs(var + 1000000) < eps) var = pos;
				else if(fabs(var - pos) > eps) {puts("NO"); exit(0);}
			}
		} else {
			a[v] = nxt_a, b[v] = nxt_b;
			dfs(v);
		}
	}
}

double ans[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);
	rep(i,0,m) {
		int u, v, c; scanf("%d %d %d", &u, &v, &c);
		g[u].pb({v, c});
		g[v].pb({u, c});
	}
	rep(i,1,n+1) {
		if(!mark[i]) {
			var = -1000000;
			a[i] = 1, dfs(i);
			if(fabs(var + 1000000) > eps) {
				for(auto u : fam[aux])
					ans[u] = (double)a[u]*var + b[u];
			} else {
				auto check = [&](double x) {
					double opa = 0.00;
					for(auto u : fam[aux])
						opa += fabs(a[u] * x + b[u]);
					return opa;
				};
				
				double l = -1e9, r = 1e9;

				rep(opa,0,1000) {
					double p1 = l + (r - l) / 3.00;
					double p2 = r - (r - l) / 3.00;

					if(check(p1) < check(p2))
						r = p2;
					else
						l = p1;
				}

				for(auto u : fam[aux])
					ans[u] = (double) a[u] * l + b[u];
			}
			aux++;
		}
	}

	puts("YES");
	rep(i,1,n+1) {
		printf("%.7lf%c", ans[i], " \n"[i==n]);
	}
}
