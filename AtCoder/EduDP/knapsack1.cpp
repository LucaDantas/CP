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

const int maxn = 110, maxw = 1e5 + 100;

int n, W, w[maxn], v[maxn];
ll dp[maxn][maxw]; //max value we can take with items up to index i and total weight w

ll solve(int i, int used){ //index of the item - weight used
	if(i == n) return 0;
	if(dp[i][used] != -1) return dp[i][used];
	
	ll add = used + w[i] <= W? solve(i+1, used + w[i]) + v[i] : 0;
	ll not_add = solve(i+1, used);
	
	return dp[i][used] = max(add, not_add);	
}

int main(){
	scanf("%d %d", &n, &W);
	rep(i,0,n)
		scanf("%d %d", &w[i], &v[i]);
	clr(dp, -1);
	printf("%lld\n", solve(0,0));
}
