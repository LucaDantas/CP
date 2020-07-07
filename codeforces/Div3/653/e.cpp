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
	int n, k;
	scanf("%d %d", &n, &k);
	priority_queue<int, vi, greater<int>> q[4];
	rep(i,0,n) {
		int t, a, b;
		scanf("%d %d %d", &t, &a, &b);
		q[2*a+b].push(t);
	}
	if(min(sz(q[1]), sz(q[2])) + sz(q[3]) < k) {
		puts("-1");
		return 0;
	}
	q[1].push(MAXN);
	q[2].push(MAXN);
	q[3].push(MAXN);
	int ans = 0;
	while(k--) {
		if(q[1].top() + q[2].top() < q[3].top()) {
			ans += q[1].top() + q[2].top();
			q[1].pop(), q[2].pop();
		}
		else {
			ans += q[3].top();
			q[3].pop();
		}
	}
	printf("%d\n", ans);
}
