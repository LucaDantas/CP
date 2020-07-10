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

// dp[i] is True if the first player (that is the player who plays right now)
// can win, otherwise it is false. And to get if the player at round i can win
// we check for every possible stone thrown if there is some in which the last
// guy can't win, and if there is then this guy can win

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	vi a(n);
	read(a,0,n);
	vector<bool> dp(k+1);
	for(int i = 1; i <= k; i++) {
		for(auto x : a) {
			if(i - x < 0)
				break;
			if(!dp[i-x])
				dp[i] = 1;
		}
	}
	puts(dp[k]? "First" : "Second");
}
