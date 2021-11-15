#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 1e6+10;

int mobius[maxn], f[maxn];
long long ans[maxn], a[maxn];

std::vector<int> pr;

void calc() { // calcula mobius
	f[1] = 1, mobius[1] = 1;
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) pr.push_back(i), f[i] = i, mobius[i] = 1;
		for(int j = 0; j < (int)pr.size() && pr[j] < f[i] && pr[j]*i < maxn; j++)
			f[pr[j] * i] = pr[j], mobius[pr[j] * i] = mobius[i] * -1;
		if(1ll * i * f[i] < maxn) f[i * f[i]] = f[i], mobius[i * f[i]] = 0;
	}
}

void doit(int n) { // normaliza o array
	for(int i = 2; i <= n; i++)
		for(int j = i+i; j <= n; j += i)
			a[j] -= a[i];
}

std::vector<long long> V[2];

long long get2(int n, int muda) {
	long long ANS = 0;
	for(int i = 1; i <= n; i++)
		ANS += std::abs(a[i] - muda * mobius[i]);
	return ANS;
}

int ini;

void get(int n) {
	ans[0] = get2(n, -ini);

	long long muda[2] = {ini, -ini}, dif = (int)(V[0].size() + V[1].size());

	int ptr[2]{};

	for(; ptr[0] < (int)(V[0].size()) && V[0][ptr[0]] >= muda[0]; ptr[0]++) dif -= 2;
	for(; ptr[1] < (int)(V[1].size()) && V[1][ptr[1]] <= muda[1]; ptr[1]++) dif -= 2;

	for(int st = 1; st < maxn; st++) {
		ans[st] = ans[st-1] - dif;

		muda[0]--;
		muda[1]++;

		for(; ptr[0] < (int)(V[0].size()) && V[0][ptr[0]] >= muda[0]; ptr[0]++) dif -= 2;

		for(; ptr[1] < (int)(V[1].size()) && V[1][ptr[1]] <= muda[1]; ptr[1]++) dif -= 2;

	}
}

int main() {
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld", a+i);
	int trash; scanf("%d", &trash);
	for(int i = 2, x; i <= n; i++)
		scanf("%d", &x), a[i] = x - a[i];

	ini = a[1];
	a[1] = 0;

	calc();
	doit(n);

	V[1].push_back(0);
	for(int i = 2; i <= n; i++)
		if(mobius[i] != 0) V[mobius[i] == 1].push_back(a[i]);

	std::sort(V[0].begin(), V[0].end());
	std::reverse(V[0].begin(), V[0].end());

	std::sort(V[1].begin(), V[1].end());

	get(n);

	int q; scanf("%d", &q);
	while(q--) { int x; scanf("%d", &x); printf("%lld\n", ans[x]); }
}
