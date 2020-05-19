#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 450;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int a[maxn];
ll dp[maxn][maxn], sum[maxn];

ll solve(int l, int r){
	if(l >= r) return 0;
	if(dp[l][r] != -1) return dp[l][r];
	
	ll ans = inf;
	
	rep(i,l,r){
		ans = min(ans, solve(l, i) + solve(i+1, r));
	}
	
	return dp[l][r] = ans + sum[r] - sum[l-1];
}

int main(){
	int n; scanf("%d", &n);
	
	rep(i,1,n+1){
		scanf("%d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
	
	clr(dp, -1);
	
	printf("%lld\n", solve(1, n));
}
