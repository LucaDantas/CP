#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 1e4+10, maxq = 105;

int a[maxn], dist[maxn<<1], qtd[maxn], n;

void add(int x) {
	for(int i = 0; i < n; i++)
		if(a[i] != a[x]) ++dist[i - x + maxn]; // adiciono o maxn pra normalizar no meio
}

void rmv(int x) {
	for(int i = 0; i < n; i++)
		if(a[i] != a[x]) --dist[i - x + maxn]; // adiciono o maxn pra normalizar no meio
}

int prox[maxn], ans[maxn][maxq], ans2[maxn][maxq];

int main() {
	int l; scanf("%d %d", &n, &l);
	for(int i = 0; i < n; i++)
		scanf("%d", a+i);

	for(int i = 0; i < l; i++)
		add(i);

	int q; scanf("%d", &q);
	std::vector<std::pair<int,int>> td(q);
	for(int i = 0, x; i < q; i++)
		scanf("%d", &x), td[i] = {x, i};
	std::sort(td.begin(), td.end());

	for(int i = 0; i <= l; i++)
		prox[i] = lower_bound(td.begin(), td.end(), std::pair<int,int>(i, 0)) - td.begin();

	for(int i = 0; i < n-l+1; i++) {
		for(int j = maxn-i; j < maxn + n-l+1-i; j++)
			if(j != maxn) ans[i][prox[dist[j]]]++;

		for(int j = 1; j < q; j++)
			ans[i][j] += ans[i][j-1];

		for(int j = 0; j < q; j++)
			ans2[i][td[j].second] = ans[i][j];

		rmv(i);
		add(i+l);
	}

	for(int j = 0; j < q; j++) {
		for(int i = 0; i < n-l+1; i++)
			printf("%d ", ans2[i][j]);
		puts("");
	}
}
