#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

// The key idea is to see that for us to form a valid
// state with exactly i items, we can either add a
// sequence of K zeros, or simply add a 1. W = 0, R = 1

// that means the recursion of dp is:
// dp[i] = dp[i-1](end with 1) + dp[i-k](end with zero)

const int maxn = 1e5 + 100, mod = 1e9 + 7;

ll dp[maxn];

inline ll MOD(ll a) {
	a %= mod;
	if(a < 0) a+= mod;
	return a;
}

int main(){
	int t, k;
	scanf("%d %d", &t, &k);
	dp[0] = 1;
	for(int i = 1; i < maxn; i++) {
		dp[i] = dp[i-1];
		if(i-k >= 0) dp[i] += dp[i-k];
		dp[i] %= mod;
	}
	dp[0] = 0;
	for(int i = 1; i < maxn; i++) {
		dp[i] += dp[i-1];
		dp[i] %= mod;
	}
	while(t--) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%lld\n", MOD(dp[b] - dp[a-1]));
	}
}
