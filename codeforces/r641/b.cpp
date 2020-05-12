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

const int maxn = 1e5 + 100;

int a[maxn], n; //we can just take the primes and check how many we can put with those primes

vi dp;

int solve(int i){
	if(i > n) return 0;
	if(dp[i] != -1) return dp[i];
	int best = 1, cont = i;
	while(i+cont <= n){
		if(a[i] < a[i+cont]){
			best = max(best, 1+solve(i+cont));
		}
		cont += i;
	}
	return dp[i] = best;
}

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		cin >> n;
		read(a,1,n+1);
		dp = vi(n+1, -1);
		int ans = 0;
		for(int i = 1; i <= n; i++)
			ans = max(ans, solve(i));
		cout << ans << '\n';
	}
}
