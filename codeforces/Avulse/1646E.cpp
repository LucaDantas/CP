#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10, logn = 20;

int qtd[logn];
bool mark[maxn*logn];

vector<int> pr;
int f[maxn];

void calc() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i, pr.push_back(i);
		for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && pr[j] * i < maxn; j++)
			f[i*pr[j]] = pr[j];
	}
}

bool good(int x) {
	vector<int> dv; int last = 0;
	while(x != 1) {
		if(f[x] == last) dv.back()++;
		else dv.push_back(1), last = f[x];
		x /= f[x];
	}
	int gcd = dv.back(); dv.pop_back();
	while(dv.size())
		gcd = __gcd(gcd, dv.back()), dv.pop_back();
	return gcd == 1;
}

int fileiras(int x, int n) {
	int val = 1;
	for(int i = 0; ; i++) {
		if(1ll * val * x > n) return i;
		val *= x;
	}
}

int main() {
	calc();
	int n, m; scanf("%d %d", &n, &m);

	for(int i = 1; i < logn; i++) {
		qtd[i] = qtd[i-1];
		for(int j = 1; j <= m; j++) {
			qtd[i] += !mark[i*j];
			mark[i*j] = 1;
		}
	}

	long long ans = 1; // 1 pra contar justamente o valor 1
	for(int i = 2; i <= n; i++)
		if(good(i)) ans += qtd[fileiras(i, n)];

	printf("%lld\n", ans);
}
