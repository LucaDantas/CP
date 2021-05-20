// divide em blocos decrescentes deve dar alguns pontos
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define ff first
#define ss second
#define pb push_back
#define all(a) (a.begin(), a.end())
#define sz(a) (int)(a.size())

constexpr int maxn = 1e6+10;

vector<int> pr;

int f[maxn];

void sieve() {
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i, pr.pb(i);
		for(int j = 0; j < sz(pr) && pr[j] <= f[i] && 1ll * i * pr[j] < maxn; j++)
			f[i * pr[j]] = pr[j];
	}
}

vector<int> dd(int x) {
	vector<int> ans;
	while(x > 1) {
		ans.pb(f[x]);
		x /= f[x];
	}
	return ans;
}

int t = 0;

vector<int> print(int qtd) {
	vector<int> ans;
	t += qtd;
	for(int i = qtd; i > 0; i--, t--)
		ans.pb(t);
	t += qtd;
	return ans;
}

int cost(int x) {
	if(x == 1) return 1;
	vector<int> d = dd(x);
	int rt = 0;
	for(int x : d)
		rt += x;
	return rt;
}

int siz(int x) { return max(1, sz(dd(x))); }

vector<int> gimme(int l) {
	if(l == 1) return vector<int>(1, ++t);
	vector<int> a = dd(l);
	vector<vector<int>> ans;
	for(int x : a)
		ans.pb(print(x));
	vector<int> ret;
	for(auto it : ans)
		for(int x : it)
			ret.pb(x);
	return ret;
}

vector<int> bora(int x) {
	vector<int> d = dd(x);
	pii melhor = {x, 0};
	for(int i = 1; i < x; i++) {
		int c = cost(i) + cost(x - i) + abs(siz(i) - siz(x - i));
		// printf("teste %d %d\n", i, c);
		melhor = min(melhor, pii(c, i));
	}
	// puts("A");
	int i = melhor.ss;
	// printf("%d %d\n", melhor.ff, melhor.ss);
	if(melhor.ff == x) return gimme(x);
	vector<int> a1 = gimme(i);
	for(int k = siz(x - i) - siz(i); k > 0; k--)
		a1.pb(++t);
	// puts("B");
	vector<int> a2 = gimme(x - i);
	for(int k = siz(i) - siz(x - i); k > 0; k--)
		a2.pb(++t);
	// puts("C");
	// printf("custo %d %d\n", melhor.ff, melhor.ss);
	vector<int> ret;
	// puts("A2");
	for(int brow : a2)
		ret.push_back(brow);
		// ret.push_back(brow), printf("%d ", brow);
	// puts("\nA1");
	for(int brow : a1)
		ret.push_back(brow);
		// ret.push_back(brow), printf("%d ", brow);
	// puts("");
	return ret;
}

int tamanho;

vector<vector<int>> get1(int l) {
	tamanho = 0;
	vector<int> a = dd(l);
	vector<vector<int>> ans;
	for(int x : a)
		ans.pb(bora(x)), tamanho += sz(ans.back());
	// puts("");
	return ans;
}

vector<int> solve(int x, int tam) {
	vector<int> ans; int sla = 0;
	for(int i = 0; i < x; i++)
		ans.pb(t+1), ans.pb(t), t += 2, sla++;
	while(sla < tam) ans.pb(t++), sla++;
	return ans;
}

vector<vector<int>> get2(int l) {
	tamanho = 0;
	int tam = 31 - __builtin_clz(l);
	vector<vector<int>> ans;
	for(int i = tam; i >= 0; i--)
		if(l & (1 << i)) ans.pb(solve(i, tam)), tamanho += sz(ans.back());
	return ans;
}

void pv(const vector<int>& v) { for(int x : v) printf("%d ", x); }

void prt(int x, vector<vector<int>> ans) {
	printf("%d\n", x);
	for(auto v1 : ans)
		for(auto k : v1)
			printf("%d ", k);
	puts("");
}

int main() {
	sieve();
	int l; scanf("%d", &l);
	vector<vector<int>> a1 = get1(l);
	int t1 = tamanho;
	// printf("%d\n", sz(a1));
	// pv(a1);
	// printf("\n");
	t = 1;
	vector<vector<int>> a2 = get2(l);
	reverse(a2.begin(), a2.end());
	int t2 = tamanho;
	t = 0;
	vector<int> solve1 = bora(l);
	if(sz(solve1) <= min(t1, t2)) {
		printf("%d\n", sz(solve1));
		pv(solve1);
		printf("\n");
		return 0;
	}
	if(t1 <= t2) prt(t1, a1);
	else prt(t2, a2);
}