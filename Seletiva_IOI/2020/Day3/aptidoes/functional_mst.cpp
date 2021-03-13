// Subtask com K_i == 2
#include<bits/stdc++.h>
using namespace std;

#define all(a) (a).begin(), (a).end()
#define pb push_back

constexpr int maxn = 1e5+10;

vector<array<int,4>> edges;

struct DSU
{
	int pai[maxn], peso[maxn];
	bool sat[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1, sat[i] = 0; }
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) {
			if(!sat[a]) {sat[a] = 1; return 1;}
			return 0;
		}
		if(sat[a] && sat[b]) return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		sat[a] |= sat[b];
		return 1;
	}
};

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0, x, y, k; i < n; i++) {
		scanf("%d %d %d", &x, &y, &k); assert(k == 2);
		int a, b; scanf("%d %d", &a, &b);
		edges.pb({x, y, a, b});
	}
	int q; scanf("%d", &q);
	while(q--) {
		int A, B; scanf("%d %d", &A, &B);
		sort(all(edges), [&](auto a, auto b){
			return 1ll*a[0]*A + 1ll*a[1]*B > 1ll*b[0]*A + 1ll*b[1]*B;
		});
		DSU dsu; long long ans = 0;
		for(auto a : edges)
			ans += dsu.join(a[2], a[3]) * (1ll*a[0]*A + 1ll*a[1]*B);
		printf("%lld\n", ans);
	}
}