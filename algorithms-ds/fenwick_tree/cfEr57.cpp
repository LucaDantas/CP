#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
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

const int maxn = 1e6 + 100;

int bit[maxn], gr[maxn], ls[maxn], n, mapped[maxn];
vector<pii> a;

void update1(int x){
	for(; x > 0; x-=(x&-x))
	//for(; x <= n; x += (x&-x))
		bit[x]++;
}

int query1(int x){
	int ans = 0;
	for(; x <= n; x += (x&-x))
	//for(; x > 0; x-=(x&-x))
		ans+=bit[x];
	return ans;
}

void update2(int x){
	//for(; x > 0; x-=(x&-x))
	for(; x <= n; x += (x&-x))
		bit[x]++;
}

int query2(int x){
	int ans = 0;
	//for(; x <= n; x += (x&-x))
	for(; x > 0; x-=(x&-x))
		ans+=bit[x];
	return ans;
}

int main(){
	FAST;
	cin >> n;
	a.resize(n);
	for(int i = 0, ent; i < n; i++){
		cin >> ent;
		a[i] = {ent, i};
	}
	sort(all(a));
	for(int i = 0; i < n; i++)
		mapped[a[i].s+1] = i+1;
	for(int i = 1; i <= n; i++){
		gr[i] = query1(mapped[i]);
		update1(mapped[i]);
	}
	clr(bit,0);
	for(int i = n; i >= 1; i--){
		ls[i] = query2(mapped[i]);
		update2(mapped[i]);
	}
	//printv(gr, 1, n+1);
	//cout << endl;
	//printv(ls, 1, n+1);
	//cout << endl;
	ll ans = 0;
	rep(i, 0, n) ans += ((ll)gr[i])*((ll)ls[i]);
	cout << ans << endl;
}
