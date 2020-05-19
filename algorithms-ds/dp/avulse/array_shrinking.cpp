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

const int maxn = 550, inf = 0x3f3f3f3f;

int a[maxn], dp[maxn][maxn];

int can[maxn][maxn], pai[maxn][maxn];

int merge(int l, int r, int& v){
	
	if(l >= r){
		assert(l == r);
		v = a[l];
		return 1;
	}
	
	if(can[l][r] != -1){
		v = pai[l][r];
		return can[l][r];
	}
	
	rep(i,l,r){
		int v_left, v_right;
		
		if(merge(l, i, v_left) && merge(i+1, r, v_right)){
			if(v_left == v_right){
				v = pai[l][r] = v_left + 1;
				return can[l][r] = 1;
			}
		}
	}
	
	v = pai[l][r] = -1;
	return can[l][r] = 0;
}

int solve(int l, int r){
	if(l > r) return 0;
	if(l == r || can[l][r]) return 1;
	if(dp[l][r] != -1) return dp[l][r];
	
	int ans = inf;
	
	rep(i,l,r){
		ans = min(ans, solve(l, i) + solve(i+1, r));
	}
	
	return dp[l][r] = ans;
}

int main(){
	int n; scanf("%d", &n);
	
	rep(i,1,n+1)
		scanf("%d", &a[i]);
	
	clr(can, -1);
	clr(dp, -1);
	clr(pai, -1);
	
	int useless = -1;			
	merge(1,n, useless);
			
	printf("%d\n", solve(1,n));
}
