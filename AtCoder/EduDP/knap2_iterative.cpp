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

// This one is almost the same as the first knapsack but we change the dimensions of the dp
// and at the end to find the answer is also different because since we calculate the 
// minimal weight for that value we might get values whose wights are greater than  W
// which means that we want to find the greatest value whose minimal weight is <= W

const int maxn = 1e5 + 100;
const ll inf = 0x3f3f3f3f3f3f3f3f;

void min_self(ll& a, ll b){
	a = min(a, b);
}

int main(){
	int n, W;
	scanf("%d %d", &n, &W);
	int max_value = n * 1000;
	vector<ll> dp(max_value + 1, inf);
	dp[0] = 0;
	for(int i = 0; i < n; i++){
		int weight, value;
		scanf("%d %d", &weight, &value);
		for(int value_already = max_value - value; value_already >= 0; --value_already){
			min_self(dp[value_already + value], dp[value_already] + weight);
		}
	}
	for(int i = max_value; i >= 0; i--)
		if(dp[i] <= W){
			printf("%d\n", i);
			return 0;
		}
}
