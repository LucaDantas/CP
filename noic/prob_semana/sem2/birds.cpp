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
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%lld", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e3 + 100, maxbirds = 1e4 + 100, inf = 0x3f3f3f3f;

ll birds[maxn], cost[maxn];

vector<vll> dp(2, vll(maxbirds, -inf)); // Trick to save memory, we only save the last and the next layer

int main(){
	ll n, W, B, X;
	scanf("%lld %lld %lld %lld", &n, &W, &B, &X);
	read(birds,1,n+1);
	read(cost,1,n+1);
	dp[0][0] = W;
	for(int i = 1; i <= n; i++) {
		for(int k = 0; k <= birds[i]; k++) {
			for(int p = k; p < maxbirds; p++) {
				if(min(dp[0][p-k] + ((i>1)?X:0), W + B*(p-k)) - cost[i] * k < 0) continue;
				dp[1][p] = max(dp[1][p], min(dp[0][p-k]+ ((i>1)?X:0) ,W + B*(p-k)) - cost[i] * k);
				if(dp[1][p] < 0) dp[1][p] = -inf;
			}
		}
		dp[0] = dp[1];
	}
	for(int i = maxbirds-1; i >= 0; i--) {
		if(dp[0][i] >= 0) { printf("%d\n", i); break; }
	}
}
