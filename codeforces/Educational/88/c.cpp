#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define double long double

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

const ll inf = 0x3f3f3f3f3f3f3f3f;

// SLA MEN NEGÓCIO BUGADO

int main(){
	int T; scanf("%d", &T);
	while(T--) {
		ll h, c, t;
		cin >> h >> c >> t;
		
		//if(t == h) {cout << 1 << '\n'; continue; }
		if(t <= (h+c)/2) {cout << 2 << '\n'; continue; }
		ll l = 1, r = 1ll<<40, best = inf;
		
		while(l <= r) {
			ll mid = (l+r) >> 1;
			ll sum = mid*h + (mid-1)*c;
			ld avr = (0.000000 + sum) / (0.000000 + mid + mid - 1);
			if(avr >= t) 
				best = mid, l = mid + 1;
			else
				r = mid - 1;
		}
		
		int ans = 2;
		ld dist = 1e18;
		
		for (int mid = best; mid <= best + 1; mid++) {
			ll sum = mid*h + (mid-1)*c;
			ld avr = (0.000000 + sum) / (0.000000 + mid + mid - 1);
			//db(avr);
			//db(abs(t - avr));
			//db(dist);
			if(abs(t - avr) < dist)
				dist = abs(t - avr), ans = mid+mid-1;
		}
		
		cout << ans << '\n';
	}
}
