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

const int maxn = 110;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m;

ll shortest(const vector<vll>& grid, const ll& start){
	vector<vll> cost(n, vll(m, inf));
	
	rep(i,0,n)
		rep(j,0,m)
			if(grid[i][j] - i - j >= start)
				cost[i][j] = grid[i][j] - i - j - start;
	
	bool tenso = false;
	
	rep(i,1,n){
		if(cost[i][0] == inf) tenso = true;
		if(tenso) cost[i][0] = inf;
		else cost[i][0] += cost[i-1][0];
	}
	
	tenso = false;
	rep(i,1,m){
		if(cost[0][i] == inf) tenso = true;
		if(tenso) cost[0][i] = inf;
		else cost[0][i] += cost[0][i-1];
	}	
	
	rep(i,1,n)
		rep(j,1,m)
			if(cost[i-1][j] < inf || cost[i][j-1] < inf)
				cost[i][j] += min(cost[i-1][j], cost[i][j-1]);
			else
				cost[i][j] = inf;
			
	return cost[n-1][m-1];
}

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		
		cin >> n >> m;
		vector<vll> grid(n, vll(m));
		
		rep(i,0,n)
			rep(j,0,m)
				cin >> grid[i][j];
				
		ll ini = grid[0][0];
		
		vll test;
		
		test.pb(ini);
		
		rep(i,0,n)
			rep(j,0,m)
				if(grid[i][j] - i - j < ini)
					test.pb(grid[i][j] - i - j);
						
		ll ans = inf;
		rep(i,0,sz(test))
			ans = min(ans, shortest(grid, test[i]));
			
		cout << ans << '\n';
	}
}
