#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#ifdef MY_DEBUG_FLAG
template<typename T> void debug(T a) { cerr << a << ' '; }
template<typename T, typename U> void debug(pair<T, U> a) { cerr << a.first << ' ' << a.second << ' '; }
template<typename T> void debug(vector<T> a) { for(auto it : a) debug(it);}
template<typename T> void debug(set<T> a) { for(auto it : a) debug(it);}
#define db(a) cerr << "DEBUG ( " << #a << " == "; debug(a); cerr << ")\n"
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
constexpr int MAXN = 1e5 + 10;
constexpr int mod = 1000000007;

int main() {
	int n; scanf("%d", &n);
	vector<double> a(n);
	rep(i,0,n) scanf("%lf", &a[i]);
	sort(all(a), greater<double>());
	if(a[0] >= 0.5) printf("%.10lf\n", a[0]);
	else {
		double ans = 0, zero = 1;
		for(auto p : a) {
			double nxt_ans = ans*(1-p) + (zero)*p;
			if(ans >= nxt_ans) break;
			ans = nxt_ans;
			zero *= (1-p);
		}
		printf("%.10lf\n", ans);
	}
}
