#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int f[maxn];
vector<int> pr;

void calc() {
	f[0] = f[1] = 1;
	for(int i = 2; i < maxn; i++) {
		if(!f[i]) f[i] = i, pr.push_back(i);
		for(int j = 0; j < (int)pr.size() && pr[j] <= f[i] && i * pr[j] < maxn; j++)
			f[i * pr[j]] = pr[j];
	}
}

vector<int> div_primos(int x) {
	vector<int> ans;
	while(x>1) {
		if(!ans.size() || ans.back() != f[x])
			ans.push_back(f[x]);
	       	x /= f[x];
	}
	return ans;
}

vector<long long> modulos[maxn];
multiset<long long> valores;

void add(int i, int val, const vector<int>& dv) {
	for(int d : dv) {
		valores.erase(valores.find(modulos[d][i%d] * d));
		modulos[d][i%d] += val;
		valores.insert(modulos[d][i%d] * d);
	}
}

int main() {
	calc();
	int t; scanf("%d", &t);
	while(t--) {
		valores.clear();

		int n, q; scanf("%d %d", &n, &q);
		vector<int> a(n);
		for(int& x : a)
			scanf("%d", &x);
		
		vector<int> dv = div_primos(n);
		for(int& d : dv) {
			d = n/d;
			modulos[d].clear(), modulos[d].resize(d);
			for(int i = 0; i < d; i++)
				valores.insert(0);
		}

		for(int i = 0; i < n; i++)
			add(i, a[i], dv);
		printf("%lld\n", *valores.rbegin());

		while(q--) {
			int p, x; scanf("%d %d", &p, &x);
			--p; //0-indexado
			add(p, -a[p], dv);
			add(p, x, dv);
			a[p] = x;
			printf("%lld\n", *valores.rbegin());
		}
	}
}

