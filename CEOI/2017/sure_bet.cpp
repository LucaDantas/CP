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
	vector<double> a(n), b(n);
	rep(i,0,n) {
		scanf("%lf %lf", &a[i], &b[i]);
	}
	
	double A = 0, B = 0, ans = 0;
	int ptrA = 0, ptrB = 0;
	sort(all(a), [](const double& x, const double& y){
		return x > y;
	});
	sort(all(b), [](const double& x, const double& y){
		return x > y;
	});

	rep(i,0,2*n) {
		if(ptrA == n || (B <= A && ptrB != n)) {
			double now = b[ptrB++];
			A--;
			B += now - 1;
			ans = max(ans, min(A, B));
		}
		else if(ptrB == n || A < B) {
			double now = a[ptrA++];
			B--;
			A += now - 1;
			ans = max(ans, min(A, B));
		}
	}

	printf("%.4lf\n", ans);
}
