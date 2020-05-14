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

const int maxn = 1e6 + 100;

int cost(const vi& a){
	int n = sz(a);
	int dp[n][3];
	dp[0][0] = dp[0][2] = a[0]; //if a[0] is on we add one because we want it to be off
	dp[0][1] = a[0]^1; //we add one if a[0] is off
	rep(i,1,n){
		dp[i][0] = dp[i-1][0] + a[i];
		dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + (a[i]^1);
		dp[i][2] = min(dp[i-1][1], dp[i-1][2]) + a[i];
	}
	return min({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}

int main(){
	FAST;
	int t; cin >> t;
	
	while(t--){
		
		int n, k; cin >> n >> k;
		string s; cin >> s;
		
		vi count(k), num(k);
		vector<vi> seq(k);
		
		rep(j,0,k){
			for(int i = j; i < n; i += k){
				count[j] += s[i]-'0';
				seq[j].pb(s[i]-'0');
			}
		}
		
		vi value(k);
		
		rep(i,0,k) value[i] = cost(seq[i]);
		
		int tot=0;
		rep(i,0,k)
			tot += count[i];
		
		int ans = 0x3f3f3f3f;
		
		rep(i,0,k) ans = min(ans, tot - count[i] + value[i]);
		
		cout << ans << endl;
	}
}
