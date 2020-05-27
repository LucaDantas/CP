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

// Claim: it is always good to finish in the last day of a month
// We do a prefix sum vector and with a binary search we find the first value
// who reduced from this one we're considering rn gets the number of days we want

int bs(ll v, vll& pref) { //we want to find the index of the first value smaller or equal to it
	int l = 0, r = sz(pref)-1, best = -1;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(pref[m] <= v)
			best = m, l = m+1;
		else
			r = m-1;
	}
	return best;
}

ll PA(ll x) {
	ll ans = (x*(x+1LL))/2LL;
	return ans;
}


int main(){
	ll n, x;
	scanf("%lld %lld", &n, &x);
	ll ans = -1;
	vll a(2*n);
	vll pref(2*n);
	vll pref_value(2*n);
	rep(i,0,n)
		scanf("%lld", &a[i]);
	
	pref[0] = a[0];
	pref_value[0] = PA(a[0]);
	
	for (int i = 1; i < n; i++) {
		pref[i] = pref[i-1] + a[i];
		pref_value[i] = pref_value[i-1] + PA(a[i]);
	}
	
	for (int i = 0; i < n; i++) {
		pref[i+n] = pref[i+n-1] + a[i];
		pref_value[i+n] = pref_value[i+n-1] + PA(a[i]);
	}

	// get the value we must do a binary search and find the first item with prefx value
	// greater or equal pref[i] - x -> pref[j]; and if that value is zero and there still is some
	// day to be considered (that is x + pref[j] < pref[i]) we must also check the suffix 
	// to find that day we want
	
	for (int i = n; i < 2*n; i++) {
		int ind = bs(pref[i] - x, pref);
		ans = max(ans, pref_value[i] - pref_value[ind] - PA(pref[i] - x - pref[ind]));
	}
	printf("%lld\n", ans);
}
