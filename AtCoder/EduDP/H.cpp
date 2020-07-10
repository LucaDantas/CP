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

const int maxn = 1e3 + 100, MOD = 1e9 + 7;

char grid[maxn][maxn];

int main(){
	int n, m; scanf("%d %d", &n, &m);
	
	vector<vi> dp(n, vi(m, 0));
	
	rep(i,0,n){
		scanf("%s", grid[i]);
	}

	for(int i = 0; i < n && grid[i][0] == '.'; i++)
		dp[i][0] = 1;
	
	for(int i = 0; i < m && grid[0][i] == '.'; i++)
		dp[0][i] = 1;
	
	rep(i,1,n)
		rep(j,1,m)
			if(grid[i][j] == '.')
				dp[i][j] = (dp[i-1][j] + dp[i][j-1])%MOD;
				
	printf("%d\n", dp[n-1][m-1]);
}
