#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define endl '\n'
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

const int maxn = 1e6 + 100;

ll n, k, Ax, Bx, Cx, Mx, Ay, By, Cy, My;
ll a[maxn], b[maxn];

ll check(ll v){
	ll ptr = n, qtd = 0;
	for(ll i = 1ll; i <= n; i++){
		while(ptr >= 1ll && a[i]+b[ptr] > v) ptr--;
		qtd += ptr;
	}
	return qtd;
}

ll bs(){
	ll l = 1, r = 1e9+100, ans;
	while(l <= r){
		int mid = ((l+r)>>1);
		if(check(mid) >= k) ans = mid, r = mid-1;
		else l = mid+1;
	}
	return ans;
}

int main(){
	FAST;
	cin >> n >> k >> Ax >> Bx >> Cx >> Mx >> Ay >> By >> Cy >> My;
	a[1] = Ax;
	b[1] = Ay;
	rep(i, 2, n+1){
		a[i] = (Bx + (Cx*a[i-1]))%(Mx);
		b[i] = (By + (Cy*b[i-1]))%(My);
	}
	sort(a+1, a+n+1), sort(b+1, b+n+1);
	cout << bs() << endl;
}
