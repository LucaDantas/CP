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

const int maxn = 1e5 + 100;

int main(){
	int n; scanf("%d", &n);
	vector<int> dp(3);
	rep(k,0,n){
		vector<int> a(3);
		trav(it, a)
			scanf("%d", &it);
		vector<int> new_dp(3, -1);
		rep(i,0,3)
			rep(j,0,3)
				if(i != j)
					new_dp[i] = max(new_dp[i], dp[j] + a[i]);
		dp = new_dp;
	}
	printf("%d\n", max({dp[0], dp[1], dp[2]}));
}
