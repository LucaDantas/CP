#include <cstdio>
#include <vector>
#include <algorithm>

// tenho q montar blocos de tamanho igual a um dos meus divisores
// então basta eu achar a media pra cada uma das classes de congruencia
// mod o primo q eu escolhi e vapo

// como eu quero deixar o maior possivel basta eu fazer eu dividido
// por cada um dos meus divisores

constexpr int maxn = 1e5+10;

int f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i;
		for(int j = 2*i; j < maxn; j += i)
			f[j] = f[i];
	}
}

std::vector<int> div(int n) {
	std::vector<int> ans;
	while(n > 1) {
		ans.push_back(f[n]);
		n /= f[n];
	}
	return ans;
}

long long cost(std::vector<int> a) {
	std::sort(a.begin(), a.end());
	long long ans = 0;
	for(int i = 0; i < (int)a.size(); i++)
		ans += std::abs(a[i] - a[((int)a.size())>>1]);
	return ans;
}

int main() {
	sieve();
	int n; scanf("%d", &n);
	std::vector<int> a(n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	long long ans = cost(a);
	std::vector<int> divi = div(n);
	for(int d : divi) {
		if(d == n) continue;
		int sz = n / d;
		std::vector<std::vector<int>> custos(sz);
		for(int i = 0; i < n; i++)
			custos[i%sz].push_back(a[i]);
		long long here = 0;
		for(int i = 0; i < sz; i++)
			here += cost(custos[i]);
		ans = std::min(ans, here);
	}
	printf("%lld\n", ans);
}