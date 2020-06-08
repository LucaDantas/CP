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

const int maxn = 1e6 + 100;

int bit[maxn];

void update(int x, int v) {
	for(; x < maxn; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

int main(){
	int n, m; scanf("%d %d", &n, &m);
	vi a(n+1);
	read(a,1,n+1);
	rep(i,1,n) update(min(a[i], a[i+1]), 1), update(max(a[i], a[i+1])+1, -1);
	// It's in purpose not to include the last because there's no one in front of it
	while(m--) {
		int type, x; scanf("%d %d", &type, &x);
		if(type == 1) {
			int v; scanf("%d", &v);
			if(n == 1) {
				a[1] = v;
				continue;
			}
			int i = x;
			if(x == 1) {
				update(min(a[i], a[i+1]), -1), update(max(a[i], a[i+1])+1, 1);
				a[i] = v;
				update(min(a[i], a[i+1]), 1), update(max(a[i], a[i+1])+1, -1);
			}
			else if(x == n) {
				update(min(a[i], a[i-1]), -1), update(max(a[i], a[i-1])+1, 1);
				a[i] = v;
				update(min(a[i], a[i-1]), 1), update(max(a[i], a[i-1])+1, -1);
			}
			else {
				update(min(a[i], a[i+1]), -1), update(max(a[i], a[i+1])+1, 1);
				update(min(a[i], a[i-1]), -1), update(max(a[i], a[i-1])+1, 1);
				a[i] = v;
				update(min(a[i], a[i+1]), 1), update(max(a[i], a[i+1])+1, -1);
				update(min(a[i], a[i-1]), 1), update(max(a[i], a[i-1])+1, -1);
			}
		}
		else if(n != 1){
			printf("%d\n", query(x));
		}
		else {
			if(x == a[1]) printf("1\n");
			else printf("0\n");
		}
	}
}
