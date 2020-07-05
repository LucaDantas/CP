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
constexpr int MAXN = 4e4 + 10;
constexpr int mod = 1000000007;

vector<int> fat;
set<int> ans;

int n;

void gen(int a, int pos, int sum) {
	if(pos >= sz(fat)) return;

	if(a == n) {
		ans.insert(sum);
		return;
	}

	if(1ll*a*fat[pos] <= 1ll*n && (n%(a*fat[pos]) == 0))
		gen(a*fat[pos], pos, sum + fat[pos]-1);
	gen(a, pos+1, sum);
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i*i <= n; i++) {
		if(n%i) continue;
		fat.eb(i);
		if(i != n/i) fat.eb(n/i);
	}
	fat.eb(n);
	sort(fat.begin(), fat.end(), greater<int>());

	gen(1,0,0); 

	printf("%d\n", sz(ans));
	for(auto it : ans) printf("%d ", it);
	printf("\n");
}
