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

const int maxn = 1e5 + 100, inf = 0x3f3f3f3f;

void min_self(int& a, int b) {
	a = min(a, b);
}

int main(){
	int n, x;
	scanf("%d %d", &n, &x);
	vi a(n), dp(x+1, inf);
	read(a,0,n);
	dp[0] = 0;
	rep(i,1,x+1) {
		allin(k, a) {
			if(i-k < 0) continue;
			min_self(dp[i], dp[i-k]+1);
		}
	}
	printf("%d\n", dp[x] == inf? -1 : dp[x]);
}
