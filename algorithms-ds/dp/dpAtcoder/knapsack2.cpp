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

const int maxn = 110, maxv = 1e5 + 100, inf = 0x3f3f3f3f;

int n, W, w[maxn], v[maxn], dp[maxn][maxv];

int solve(int i, int value){ //we want the minimal weight using items up to i and with that value
	if(i==n && value) return inf;
	if(i==n) return 0;
	if(dp[i][value] != -1) return dp[i][value];
	
	int add = v[i] <= value? solve(i+1, value - v[i]) + w[i] : inf;
	int not_add = solve(i+1, value);
	int ans = min(add, not_add);
	if(ans > W) ans = inf;
	return dp[i][value] = ans;
}

int main(){
	scanf("%d %d", &n, &W);
	
	rep(i,0,n)
		scanf("%d %d", &w[i], &v[i]);
		
	clr(dp, -1);
	
	for(int i = maxv - 100; i >= 0; i--)
		if(solve(0, i) < inf){
			printf("%d\n", i);
			return 0;
		}
	
}
