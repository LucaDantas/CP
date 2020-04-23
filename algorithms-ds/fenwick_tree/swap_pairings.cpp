#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mkp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<
#define int long long

const int maxn = 1e5 + 100;
int a[maxn], bit[maxn+1];
vector<pii> paris;

void update(int x, int v){
	for(; x <= maxn; x+=(x&-x))
		bit[x] += v;
}

int query(int x){
	int ans = 0;
	for(; x > 0; x-=(x&-x))
		ans += bit[x];
	return ans;
}

int32_t main(){
	FAST;
	int n;
	cin >> n;
	read(a, 1, n+1);
	rep(i, 1, n+1) update(i, 1);
	map<int, int> mp;
	for(int i = 1; i <= n; i++){
		if(mp.find(a[i]) != mp.end()){
			paris.pb(mkp(mp[a[i]], i));
			mp.erase(a[i]);
		}
		else{
			mp.insert(mkp(a[i], i));
		}
	}
	sort(all(paris));
	int ans = 0;
	for(int i = 0; i < n/2; i++){
		ans += query(paris[i].s-1) - query(paris[i].f);
		update(paris[i].f, -1), update(paris[i].s, -1);
	}
	cout << ans << endl;
}
