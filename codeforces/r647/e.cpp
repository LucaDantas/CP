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

const int inf = 0x3f3f3f3f, mod = 1e9 + 7;

// const int maxn = 1e5 + 100;

// We have to go in non-increasing order

int power(int b, int e) {
	int r = 1;
	while(e) {
		if(e&1) r = (ll)r*b%mod;
		b = (ll)b*b%mod;
		e >>= 1;
	}
	return r;
}

int main(){
	int T; scanf("%d", &T);
	while(T--) {
		int n, p;
		scanf("%d %d", &n, &p);
		vi a(n);
		read(a,0,n);
		if(p == 1) {
			if(n&1) printf("1\n");
			else printf("0\n");
			continue;
		}
		sort(all(a), greater<int>());
		int prev = a[0];
		bool infinity = false;
		ll sum = 0, times = 0;
		for(auto x : a) {
			if(infinity) {
				sum -= power(p, x);
				sum %= mod;
				if(sum < 0) sum += mod;
				continue;
			}
			 int multp = min(prev - x, 64);
			 while(multp-- && !infinity) {
			 	times *= p;
			 	if(times > inf) infinity = true;
			 }
			 
			if(times == 0) {
				sum += power(p, x);
				sum %= mod;
				times++;
			}
			else {
				sum -= power(p, x);
				sum %= mod;
				if(sum < 0) sum += mod;
				times--;
			}
			prev = x;
		}
		sum %= mod;
		if(sum < 0) sum += mod;
		printf("%lld\n", sum);
	}
}
