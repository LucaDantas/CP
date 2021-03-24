#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e7+10;

int f[maxn], qtd[maxn];
vector<int> pr;

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) {
			f[i] = i;
			qtd[i] = 1;
			pr.push_back(i);
		}
		for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && 1ll*pr[j]*i < maxn; j++)
			f[i * pr[j]] = pr[j], qtd[i * pr[j]] = qtd[i] + (f[i] != pr[j]);
	}
}

int get(int c, int d, int div) {
	if((div + d) % c) return 0;
	return 1<<qtd[(div + d) / c];
}

int main() {
	sieve();
	int t; scanf("%d", &t);
	while(t--) {
		int c, d, x; scanf("%d %d %d", &c, &d, &x);
		long long ans = 0;
		for(int i = 1; i*i <= x; i++) {
			if(x%i) continue;
			ans += get(c, d, i);
			if(i != x/i) ans += get(c, d, x/i);
		}
		printf("%lld\n", ans);
	}
}