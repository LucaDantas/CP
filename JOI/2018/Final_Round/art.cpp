#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<ll,ll>;

#define ff first
#define ss second
#define rall(a) (a).rbegin(), (a).rend()

int main() {
	int n; scanf("%d", &n);
	vector<pii> a(n);
	for(auto& it : a)
		scanf("%lld %lld", &it.ff, &it.ss);
	sort(rall(a));
	// Os caras com maior peso vem na frente
	ll maior = -0x3f3f3f3f3f3f3f3f, ans = -0x3f3f3f3f3f3f3f3f;
	for(int i = 0; i < n; i++) {
		maior = max(maior + a[i].ss, a[i].ss - a[i].ff);
		ans = max(ans, maior + a[i].ff);
	}
	printf("%lld\n", ans);
}