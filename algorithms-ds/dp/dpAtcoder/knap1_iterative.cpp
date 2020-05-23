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

// I'm doing the code pretty much just like Errichto did in the stream to learn iterative dp
// The solution to this one is to add each box to the intervals that it fits, which are
// from weights starting with zero and up to W - weight, but we do it decreasingly
// because if we do it otherwise it might happen that we repeat the same item more than once
// which is not allowed in this question, but if it was we could simply invert the order

void max_self(ll& a, ll b){
	a = max(a, b);
}

int main(){
	int n, W;
	scanf("%d %d", &n, &W);
	vector<ll> dp(W + 1);
	
	for(int i = 0; i < n; i++){
		int weight, value;
		scanf("%d %d", &weight, &value);
		for(int weight_already = W - weight; weight_already >= 0; --weight_already){
			max_self(dp[weight_already + weight], dp[weight_already] + value);
		}
	}
	
	ll ans = -1;
	
	for(auto it : dp)
		max_self(ans, it);
	
	printf("%lld\n", ans);
}
