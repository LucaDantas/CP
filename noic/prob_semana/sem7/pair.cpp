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

const int maxn = 3e5+100, maxl = 21;

int gcd(int a,int b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

int n, a[maxn], sparse[maxn][maxl], lg[maxn];

void build() {
	for(int i = 1; i <= n; i++) {
		sparse[i][0] = a[i];
	}
	for(int k = 1; k < maxl; k++) {
		for(int i = 1; i <= n - (1 << k)+1; i++) {
			sparse[i][k] = gcd(sparse[i][k-1], sparse[i+ (1 << (k-1)) ][k-1]);
		}
	}

	lg[1] = 0;
	for(int i = 2; i < maxn; i++) lg[i] = lg[i>>1]+1;
}

int query(int l, int r) {
	int tam = lg[r-l+1];
	return gcd(sparse[l][tam], sparse[r-(1<<tam)+1][tam]);
}

int main(){
	scanf("%d", &n);
	read(a,1,n+1);
	build();

	int maior = 0;
	vi ans[n+1];

	set<pii> s;

	query(1,n);

	for(int pos = 1; pos <= n; pos++) {
		int l = 1, r = pos, ansl = -1, ansr = -1;
		while(l <= r) {
			int m = (l+r) >> 1;
			// db(m);
			// db(query(m,pos));
			if(query(m, pos) == a[pos])
				ansl = m, r = m-1;
			else
				l = m+1;
		}

		l = pos, r = n;
		while(l <= r) {
			int m = (l+r) >> 1;
			// db(query(pos,m));
			if(query(pos, m) == a[pos])
				ansr = m, l = m+1;
			else
				r = m-1;
		}

		// db(ansl);
		// db(ansr);
		// puts("");

		if(ansr - ansl >= maior && !s.count(mp(ansl, ansr))) {
			s.insert(mp(ansl,ansr));
			ans[ansr-ansl].pb(ansl);
			maior = max(maior, ansr-ansl);
		}
	}

	printf("%d %d\n", sz(ans[maior]), maior);
	rep(i,0,sz(ans[maior])) printf("%d%c", ans[maior][i], " \n"[i==sz(ans[maior])-1]);
}
