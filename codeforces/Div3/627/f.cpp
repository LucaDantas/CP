#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define endl '\n'
#define ll long long
#define f first
#define s second
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define debug(x) cout << "DEBUG " << x << endl
#define debug2(x, y) cout << "DEBUG " << x << " " << y << endl
#define debug3(x, y, z) cout << "DEBUG " << x << " " << y << " " << z<< endl
#define debug4(x, y, z, o) cout << "DEBUG " << x << " " << y << " " << z<< " " << o << endl
#define max3(x, y, z) max(x, max(y, z))

const int maxn = 2e5 + 100;
vector<vector<int> > g(maxn);
int dp[maxn], val[maxn], ans[maxn];

void dfs(int i = 0, int p = -1){
	dp[i] = val[i];
	for(auto it : g[i]){
		if(it == p) continue;
		dfs(it, i);
		dp[i] += max(0, dp[it]); 
	}
}

void dfs2(int i = 0, int p = -1){
	ans[i] = dp[i];
	for(auto it : g[i]){
		if(it == p) continue;
		int kkk = dp[it];
		dp[i] -= max(0,dp[it]);
		dp[it] += max(dp[i], 0);
		dfs2(it, i);
		dp[i] += max(0,kkk);
	}
}

int main(){
	FAST;
	int n;
	cin >> n;
	for(int i = 0, a; i < n; i++){
		cin >> a;
		if(!a) a = -1;
		val[i] = a;
	}
	for(int i = 1, a, b; i < n; i++){
		cin >> a >> b;
		g[a-1].pb(b-1);
		g[b-1].pb(a-1);
	}
	dfs();
	dfs2();
	for(int i = 0; i < n; i++)
		cout << ans[i] << ' ';
	cout << endl;
}
