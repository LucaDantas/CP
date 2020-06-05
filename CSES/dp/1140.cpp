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

const int maxn = 2e5 + 100;

int main(){
	int n; scanf("%d", &n);
	vi a(n), b(n), p(n);
	map<int, int> compress;
	rep (i,0,n) {
		scanf("%d %d %d", &a[i], &b[i], &p[i]);
		b[i]++; //We do this to be able to count from this day, not from the next
		compress[a[i]], compress[b[i]];
	}
	
	int coord = 0;
	trav(it, compress) {
		it.second = coord++;
	}
	
	vll dp(coord);
	
	vi begin[coord];
	
	rep (i,0,n) {
		begin[compress[a[i]]].pb(i);
	}
	
	for (int i = coord - 2; i >= 0; i--) {
		dp[i] = dp[i+1];
		for(auto d : begin[i]) {
			dp[i] = max(dp[i], dp[compress[b[d]]] + p[d]);
		}
	}
	
	printf("%lld\n", dp[0]);
}
