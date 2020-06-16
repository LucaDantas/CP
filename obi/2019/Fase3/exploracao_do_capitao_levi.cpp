#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
// #define mp make_pair
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

int n;

struct Point{
	int x, y, compressed;
	ll val;
} pts[maxn];

void compress() {
	map<ll, int> mp;
	for(int i = 0; i < n; i++) {
		mp[pts[i].val];
	}
	int aux = 0;
	for(auto &it : mp)
		it.second = ++aux;
	for(int i = 0; i < n; i++)
		pts[i].compressed = mp[pts[i].val];
}

int bit[maxn+1];

void update(int x, int v) {
	for(; x <= maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int main(){
	int p, q;
	scanf("%d %d %d", &n, &p, &q);

	if(q < 0) q *= -1, p *= -1;

	for(int i = 0; i < n; i++) {
		scanf("%d %d", &pts[i].x, &pts[i].y);
		pts[i].val = 1ll*q*pts[i].y - 1ll*p*pts[i].x;
	}

	sort(pts, pts+n, [](const Point& lhs, const Point& rhs) {
		return lhs.x > rhs.x;
	});

	compress();

	ll ans = 0;

	for(int i = 0; i < n; i++) {
		ans += query(maxn) - query(pts[i].compressed-1);
		update(pts[i].compressed, 1);
	}

	printf("%lld\n", ans);
}
