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

const int maxn = 1e5 + 100, MOD = 1e9 + 7;

inline int mod(int a, int b){ a %= b; if (a < 0) a += b; return a;} 

int main(){
	int n;
	scanf("%d", &n);
	vector<int> dp(n+1), pref(n+1);
	dp[1] = pref[1] = 1;
	for (int i = 2; i <= n; i++) {
		int last;
		scanf("%d", &last);
		if(last) { //that means the item now is in front of the last (pref[j-1])
			for (int j = i; j >= 1; j--) { //calculate the values based on the sum of all the next ones
				dp[j] = mod(pref[j-1],MOD);
			}
			//recalculate the prefix sum of values
			for (int j = 1; j <= i; j++) {
				pref[j] = mod(pref[j-1] + dp[j],MOD);
			}
		}
		else { //that means the item is behind the last one (pref[i] - pref[j-1])
			for (int j = i; j >= 1; j--) { //calculate the values based on the sum of all the next ones
				dp[j] = mod(pref[i-1] - pref[j-1],MOD); //in this case we consider i-1 instead of i because in the last iteration when
														//we calculated the prefix sum i was what now is i-1
			}
			//recalculate the prefix sum of values
			for (int j = 1; j <= i; j++) {
				pref[j] = mod(pref[j-1] + dp[j],MOD);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = mod(ans + dp[i],MOD);
	printf("%d\n", ans);
}
