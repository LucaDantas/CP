#include "boxes.h"
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

#define pb push_back
#define sz(a) (int)(a.size())

using ll = long long;

ll delivery(int N, int K, int L, int p[]) {
	vector<int> esq = {0}, dir;
	for(int i = 0; i < N; i++) {
		if(!p[i]) continue;
		if(p[i] <= L/2)
			esq.pb(p[i]);
		if(p[i] >= L - (L-1)/2)
			dir.pb(L - p[i]);
	}
	dir.pb(0);
	reverse(dir.begin(), dir.end());
	vector<ll> pref(sz(esq)), suf(sz(dir));
	for(int i = 1; i < sz(esq); i++)
		pref[i] = 2ll*esq[i] + (i>=K?pref[i-K]:0);
	for(int i = 1; i < sz(dir); i++)
		suf[i] = 2ll*dir[i] + (i>=K?suf[i-K]:0);
	ll ans = (sz(pref)?pref.back():0) + (sz(suf)?suf.back():0);
	for(int i = 0; i <= min(K, sz(esq)-1); i++) {
		ll here = L + pref[sz(esq)-1-i];
		here += suf[max(0, sz(dir)-1-(K-i))];
		ans = min(ans, here);
	}
	return ans;
}
