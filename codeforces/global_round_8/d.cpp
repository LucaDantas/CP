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

int aparece[21];

int tree[4*maxn];

void update(int node, int i, int j, int l, int r, int k) {
	if(i > r || j < l) return;
	if(i >= l && j <= r) {
		tree[node] |= (1<<k);
		return;
	}
	int m = (i+j) >> 1;
	update(2*node,i,m,l,r,k);
	update(2*node+1,m+1,j,l,r,k);
}

int query(int node, int i, int j, int pos) {
	if(i == j) return tree[node];
	int m = (i+j) >> 1;
	if(pos <= m) return tree[node]|query(2*node,i,m,pos);
	else return tree[node]|query(2*node+1,m+1,j,pos);
}

int main(){
	int n; scanf("%d", &n);
	vi a(n); read(a,0,n);

	rep(i,0,n) {
		rep(k,0,20) {
			if(a[i] & (1 << k))
				aparece[k]++;
		}
	}

	for(int k = 0; k < 21; k++) { // Pra cada bit a gente da xor dele no prefixo [1..aparece[k]] com seg
		update(1,1,n,1,aparece[k],k);
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		int now = query(1,1,n,i);
		ans += 1ll*now*now;
	}
	printf("%lld\n", ans);
}
