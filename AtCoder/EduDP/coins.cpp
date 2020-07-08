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

//this code is just like the one Errichto did in his stream
//if I were to do it iteractively we'd need n² space too to do it
// I still think I'll try to code it tomorrow but the idea is the same

// the value of dp[i] in the current iteration is the propability of having already
// i in the last iteration (represent by dp[i] before updating - remember we do
// in decreascent order) multiplied by the probability of having tails now
// + probability of having i-1 heads in the last iteration multiplied by the
// probability of having heads now 

const int maxn = 1e5 + 100;

int main(){
	int n;
	scanf("%d", &n);
	vector<double> dp(n + 1);
	//dp[i] - prob of having exactly i heads
	dp[0] = 1;
	for(int coin = 0; coin < n; ++coin)
	{
		double p;
		scanf("%lf", &p);
		for (int i = coin + 1; i >= 0; i--)
		{
			dp[i] = (i == 0? 0 : dp[i-1] * p) + dp[i] * (1 - p);
		}
	}
	double answer = 0;
	for(int i = 0; i <= n/2; i++)
		answer += dp[n-i];
    printf("%.10lf\n", answer);
}
