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

int n, k, ans;
vi a;

void solve(int v, int prime, bool even) {
	if(prime == k) {
		if(even) ans += n/v;
		else ans -= n/v;
		return;
	}
	solve(v, prime+1, even);
	if(1ll*v*a[prime] <= 1ll*n) {
		solve(v*a[prime], prime+1, !even);
	}
}

int main(){
	scanf("%d %d", &n, &k);
	a.resize(k);
	read(a,0,k);
	solve(1,0,true);
	printf("%d\n", ans);
}
