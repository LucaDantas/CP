#include <bits/stdc++.h>
using namespace std;

#define int long long

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
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%lld", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxv = 1e10;

// We have to do a ternary search to find the min-peak of the function
// For us to get the answer for a certain value we do a binary search
// and based on its position we can find the number of blocks there are to add and remove

int n, A, R, M;

vi a, pref;

int bs(int v) {
	int l = 1, r = n, ans = 0;
	while(l <= r) {
		int m = (l+r) >> 1;
		if(a[m] <= v)
			ans = m, l = m+1;
		else
			r = m-1;
	}
	return ans;
}

int value(int v) {
	int pos = bs(v);
	int add = pos*v - pref[pos];
	int remove = pref.back() - pref[pos] - (n-pos)*v;
	int cost = min(add, remove) * M;
	if(add > remove)
		cost += (add-remove)*A;
	else
		cost += (remove-add)*R;
	return cost;
}

int32_t main(){
	scanf("%lld %lld %lld %lld", &n, &A, &R, &M);
	M = min(M, A + R);

	a.resize(n+1);
	read(a,1,n+1);
	sort(a.begin()+1, a.end());
	pref = a;
	
	rep(i,1,n+1) pref[i] += pref[i-1];
	
	// now we have to do a ternary search
	// it works by selecting three values and deciding based on it where to go
	// we choose the items at (r-l)/3, (r-l)/3 + 1 , 2*(r-l)/3, 2*(r-l)/3 - 1
	// we check to where the array is descending and go to that interval
	
	int l = 1, r = maxv, ans = 0x3f3f3f3f3f3f3f3f;
	
	while(l <= r) {
		int sz = r-l;
		int left = l + sz/3;
		int right = l + 2*sz/3;
		
		int v1 = value(left);
		int v2 = value(left+1);
		int v3 = value(right);
		int v4 = value(right-1);
		
		ans = min({ans, v1, v2, v3, v4});
		
		bool dl = v1 < v2;
		bool dr = v3 < v4;
		
		if(!dl && !dr)
			l = left+1, r = right-1;
		else if(dl)
			r = left-1;
		else
			l = right+1;
	}
	
	printf("%lld\n", ans);
}
