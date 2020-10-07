#include "shoes.h"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define pb push_back
#define ff first
#define ss second
#define fast ios_base::sync_with_stdio(false), cout.tie(nullptr), cin.tie(nullptr)
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()

constexpr int inf = 0x3f3f3f3f;
constexpr int MAXN = 2e5 + 10;
constexpr int LOGN = 20;
constexpr int mod = 1000000007;

int bit[MAXN], n;

void upd(int x, int v) {
	for(x++; x <= n; x += x&-x)
		bit[x] += v;
}

int query(int x) {
	int ans = 0;
	for(x++; x > 0; x -= x&-x)
		ans += bit[x];
	return ans;
}

ll ans = 0;

vi par, act;

long long count_swaps(std::vector<int> a) {
	n = sz(a);
	
	par.resize(n); act.resize(n);
	vector<queue<int>> q(n+1);
	
	rep(i,0,n) {
		if(q[abs(a[i])].empty() || a[q[abs(a[i])].front()] == a[i]) {
			q[abs(a[i])].push(i);
			if(a[i] > 0) ans++;	
		}
		else {
			par[ q[ abs(a[i]) ].front() ] = i;
			par[i] = q[ abs(a[i]) ].front();
			q[ abs(a[i]) ].pop();
		}
	}
	
	rep(i,0,n) {
		act[i] = 1;
		upd(i,1);
	}
	
	rep(i,0,n) {
		if(!act[i]) continue;
		ans += query(par[i]-1) - 1; // everyone is already off behind him
		upd(par[i], -1), upd(i, -1);
		act[i] = 0, act[par[i]] = 0;
	}
	
	return ans;
}

