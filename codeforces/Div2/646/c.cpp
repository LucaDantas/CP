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

const int maxn = 1000 + 100;

// dp[vital][non-vital] is true if who plays now can win
// and false if it can't
// the transition is: dp[v][nv] = (!dp[v-1][nv] || !dp[v][nv-1])
// base case: dp[1][nv] = true
// we must always check if there is some non-vital to remove

int dp[maxn][maxn];

int solve(int v, int tot) {
	if(v == 1) return true;
	if(dp[v][tot] != -1) return dp[v][tot];
	if(tot > v) {
		// those are the possibilities of choosing a vital or a non_vital
		return dp[v][tot] = (!solve(v-1, tot-1) || !solve(v, tot-1));
	}
	return dp[v][tot] = !solve(v-1, tot-1);
}

int main(){
	int t; scanf("%d", &t);
	while(t--) {
		
		clr(dp,-1);
		
		int n, x;
		scanf("%d %d", &n, &x);
		
		int vital = 0, tot = n-1;
		
		rep(i,1,n) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(x == u || x == v) vital++;
		}
		
		//non_vital -= vital;
		if(n == 1) puts("Ayush");
		else puts(solve(vital, tot)? "Ayush" : "Ashish");
	}
}
