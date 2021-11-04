#include <cstdio>
#include <vector>

using ll = long long;

int N;

ll vivo = 0;

std::vector<int> ids;
std::vector<ll> now, prox;

int get(ll mask, int pos) {
	if(vivo & (1ll << pos))
		return (mask & (1ll << pos)) > 0;
	return 2;
}

void set(ll& mask, int pos, int val) {
	mask |= (1ll << pos);
	if(!val) mask ^= (1ll << pos);
}

void operation(ll mask) {
	int cnt[3]{};
	for(const int& x : ids) cnt[get(mask, x)]++;

	for(int i = 0; i <= cnt[2]; i++) {
		ll aq = mask;
		int hm = cnt[0] + i;

		for(const int& x : ids)
			set(aq, x, hm <= 0), --hm;

		prox.push_back(aq);
	}
}

bool bom(const ll& mask) {
	int first_1 = 50, last_0 = -1;
	for(int i = 0; i < N; i++) {
		if((mask & (1ll << i)) > 0 && first_1 == 50) first_1 = i;
		if((mask & (1ll << i)) == 0) last_0 = i;
	}
	return first_1 > last_0;
}

std::vector<int> sv[10];

int main() {
	int n, k; scanf("%d %d", &n, &k); N = n;
	now.push_back(0);

	ll c1 = 0, c2 = 0;
	for(int i = 0; i < k; i++) {
		c1 = c2;
		int qtd; scanf("%d", &qtd);
		sv[i].resize(qtd);
		for(int& x : sv[i])
			scanf("%d", &x), --x, c2 |= (1ll << x);
	}

	if(n == 1 || (int)sv[k-1].size() == n) return puts("ACCEPTED"), 0;
 
	if(c1 != (1ll << N) - 1 && (int)sv[k-1].size() != n)
		return puts("REJECTED"), 0;

	for(int i = 0; i < k; i++) {
		ids = sv[i];

		for(const ll& mask : now)
			operation(mask);

		for(int x : ids)
			vivo |= (1ll << x);

		std::swap(now, prox);
		prox.clear();
	}

	bool ok = 1;
	for(const ll& mask : now)
		ok &= bom(mask);

	puts(ok ? "ACCEPTED" : "REJECTED");
}
