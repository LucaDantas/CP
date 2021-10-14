#include <cstdio>
#include <algorithm>
#include <map>

#define int long long

constexpr int maxn = 2e5+10, B = 300;

int a[maxn], val[maxn], cnt[maxn];
long long ans[maxn], resp[maxn];

struct Query {
	int l, r, k, id;
	bool operator<(const Query& o) const {
		if(l / B == o.l / B) return r < o.r;
		return l < o.l;
	}
} qr[maxn];

std::map<int,int> compress;

int32_t main() {
	int n, q; scanf("%lld %lld", &n, &q);
	
	for(int i = 1; i <= n; i++)
		scanf("%lld", a+i), compress[a[i]] = 1;

	int aux = 0;
	for(auto& it : compress)
		++aux, val[aux] = it.first, it.second = aux;

	for(int i = 1; i <= n; i++)
		a[i] = compress[a[i]];

	for(int i = 0, l, r, k; i < q; i++)
		scanf("%lld %lld %lld", &l, &r, &k), qr[i] = {l, r, k, i};

	std::sort(qr, qr+q);

	int l = 0, r = 0;
	for(int i = 0; i < q; i++) {
		auto [L, R, K, id] = qr[i];

		for(; l > L;) --l, cnt[a[l]]++, ans[cnt[a[l]]] += val[a[l]];
		for(; r < R;) ++r, cnt[a[r]]++, ans[cnt[a[r]]] += val[a[r]];

		for(; l < L; l++) ans[cnt[a[l]]] -= val[a[l]], cnt[a[l]]--;
		for(; r > R; r--) ans[cnt[a[r]]] -= val[a[r]], cnt[a[r]]--;

		resp[id] = ans[K];
	}

	for(int i = 0; i < q; i++)
		printf("%lld\n", resp[i]);
}
