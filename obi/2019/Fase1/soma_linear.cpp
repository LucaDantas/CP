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

const int maxn = 5e5 + 100;

int main(){
	int n, k, now = 0; scanf("%d %d", &n, &k);
	vi a(n), zeros, normal;
	read(a,0,n);
	// Transform in a zeros and a normal array
	rep(i,0,n) {
		if(a[i] != 0) zeros.pb(now), normal.pb(a[i]), now = 0;
		else now++;
	}
	zeros.pb(now);
	if(k == 0) {
		ll ans = 0;
		allin(it, zeros) ans += 1ll*it*(it+1)/2ll;
		printf("%lld\n", ans);
		return 0;
	}
	int tam = sz(normal);
	ll ans = 0;
	int l = 0, r = 0, sum = normal[0];

	for(; l < tam; l++) {
		while(r + 1 < tam && sum < k)
			sum+=normal[++r];
		if(sum == k) ans += 1ll*(zeros[l]+1)*(zeros[r+1]+1);
		sum -= normal[l];
	}
	
	printf("%lld\n", ans);
}
