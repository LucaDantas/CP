#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,a,b) for(int i=(a); i>=(b); i--)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 2e5+10, maxl = 21;

int a[maxn];

ll bit[maxn];

void update(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

ll query(int x) {
	ll ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int find(ll v) {
	int ret = 0;
	for(int b = maxl; b >= 0; b--) {
		if(ret + (1 << b) < maxn && bit[ret + (1 << b)] < v) {
			ret += (1 << b), v -= bit[ret];
		}
	}
	return ret+1;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);

	rep(i,1,n+1) scanf("%d", a + i), update(i,a[i]);

	while(q--) {
		int p, x;
		scanf("%d %d", &p, &x);
		update(p,-a[p]);
		update(p,x);
		a[p] = x;

		int prox = 1, ans = -1;

		while(1) {
			ll k = query(prox)*2;
			prox = find(k); // returns the lower bound of k
			if(prox > n || query(prox) < k) break;
			if(query(prox-1) == a[prox]) {
				ans = prox;
				break;
			}
		}
		printf("%d\n", ans);
	}
}
