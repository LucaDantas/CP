#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 510, maxSZ = 2e5, mod = 1000000007;

int fat[maxSZ+maxn], inv_fat[maxSZ+maxn], inv[maxSZ+maxn], botar[maxSZ+maxn+1][maxn];

void add(int& a, int b) { a += b; if(a >= mod) a -= mod; }

int am(int a, int b) { add(a, b); return a; }

int choose(int a, int b) { return (int)(1ll * fat[a] * inv_fat[b] % mod * inv_fat[a-b] % mod); }

void calc() {
	fat[0] = fat[1] = inv_fat[1] = inv_fat[0] = inv[1] = 1;
	for(int i = 2; i < maxSZ+maxn; i++) {
		fat[i] = (int)(1ll * fat[i-1] * i % mod);
		inv[i] = mod - (int)(1ll * (mod/i) * inv[mod%i] % mod);
		inv_fat[i] = (int)(1ll * inv_fat[i-1] * inv[i] % mod);
	}

	for(int i = 1; i < maxn; i++)
		botar[0][i] = 1;
	for(int i = 0; i < maxSZ; i++)
		botar[i][0] = i+1;
	for(int i = 1; i < maxSZ; i++)
		for(int j = 1; j < maxn; j++)
			botar[i][j] = am(botar[i-1][j], choose(i+j, j));
}

struct Par
{
	int l, r;
} itv[maxn];

struct Grp
{
	int l, r, val; std::vector<int> p;
	void calc() {
		int qtd = (int)(p.size());
		val = 0;
		for(int i = 0; i < qtd; i++)
			add(val, (int)(1ll * botar[r-l][qtd-i-1] * p[i] % mod));
	}
} blocks[1<<13];

std::vector<int> divisoes;

int main() {
	calc();

	for(int i = 1; i <= 5000; i++)
		divisoes.push_back(i * maxSZ);
	
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &itv[i].l, &itv[i].r), ++itv[i].r, divisoes.push_back(itv[i].l), divisoes.push_back(itv[i].r);

	std::sort(divisoes.begin(), divisoes.end());
	divisoes.resize(std::unique(divisoes.begin(), divisoes.end()) - divisoes.begin());

	int inicio = divisoes.front(), t = (int)(divisoes.size());
	for(int i = 1; i < t; i++)
		blocks[i].l = inicio, blocks[i].r = divisoes[i]-1, inicio = divisoes[i];

	for(int qr = 0; qr < n; qr++) {
		int soma = 1;
		auto [l, r] = itv[qr]; --r;
		for(int i = 0; i < t; i++) {
			int val = blocks[i].val;

			if(blocks[i].l >= l && blocks[i].r <= r)
				blocks[i].p.push_back(soma), blocks[i].calc();

			add(soma, val);
		}
	}

	int ans = 0;
	for(int i = 0; i < t; i++)
		add(ans, blocks[i].val);

	printf("%d\n", ans);
}
