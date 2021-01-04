#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 5e5+10, mod = 1e9+7;

struct DSU
{
	int pai[maxn], peso[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1;}
	int find(int x) {return pai[x]==x?x:pai[x] = find(pai[x]);}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return false;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		return true;
	}
} dsu;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<int> resp;
	for(int i = 0, k, a, b; i < n; i++) {
		scanf("%d", &k); --k;
		scanf("%d", &a); --a;
		if(k) {
			scanf("%d", &b); --b;
			if(dsu.join(a, b)) resp.pb(i+1);
		} else if(dsu.join(a, m)) resp.pb(i+1);
	}
	int pot = 0, ans = 1;
	for(int i = 0; i <= m; i++)
		if(dsu.find(i) == i) pot += dsu.peso[dsu.find(i)]-1;
	for(int i = 0; i < pot; i++) {
		ans += ans;
		if(ans >= mod) ans -= mod;
	}
	printf("%d %d\n", ans, pot);
	for(int x : resp)
		printf("%d ", x);
	printf("\n");
}