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

int t;

vector<int> print(int qtd) {
	t += qtd;
	for(int i = qtd; i > 0; i--, t--)
		ans.pb(t);
	t += qtd;
}

int main() {
	sieve();
	int l; scanf("%d", &l);
	vector<int> a = dd(l);
	int sz = 0;
	for(int x : a)
		sz += x;
	printf("%d\n", sz);
	for(int x : a)
		print(x);
	puts("");
}