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

int tamanho;

vector<vector<int>> get1(int l) {
	tamanho = 0;
	vector<int> a = dd(l);
	vector<vector<int>> ans;
	for(int x : a)
		ans.pb(print(x)), tamanho += x;
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

void pv(vector<int> v) { for(int x : v) printf("%d ", x); }

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
	t = 1;
	vector<vector<int>> a2 = get2(l);
	reverse(a2.begin(), a2.end());
	int t2 = tamanho;
	if(t1 <= t2) prt(t1, a1);
	else prt(t2, a2);
}