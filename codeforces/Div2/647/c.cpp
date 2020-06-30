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

const int maxl = 61;

// the answer is to find the sum of the sequence 1 + 2 + 1 + 3 + 1 + 2 + 4 +...

// we can do this in an iteration because the sum of the given value (i.e. the max/middle number of the sequence)
// is: seq[mid] = 2*(seq[mid-1]) + mid

ll seq[maxl], tam[maxl];

int bs(ll v) {
	int l = 1, r = maxl - 1, ans = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(v >= tam[m]) ans = m, l = m+1;
		else r = m-1;
	} 
	return ans;
}

int main(){
	int t; scanf("%d",&t);
	while(t--) {
		ll n;
		scanf("%lld", &n);
		rep(i,1,maxl) {
			seq[i] = 2*seq[i-1] + i;
			tam[i] = 2*tam[i-1] + 1;
		}
		ll ans = 0;
		while(n) {
			int pos = bs(n);
			n -= tam[pos];
			ans += seq[pos];
			if(n) n--, ans+=pos+1;
		}
		printf("%lld\n", ans);
	}
}
