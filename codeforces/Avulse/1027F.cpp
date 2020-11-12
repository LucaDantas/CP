#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e6+10;

struct DSU
{
	int pai[maxn], peso[maxn], maior[maxn][2], edges[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, peso[i] = 1, edges[i] = 0, maior[i][0] = i;}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	void join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b)
			return (void)(edges[a]++);
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		edges[a] += edges[b]+1;
		if(maior[b][0] > maior[a][0])
			maior[a][1] = max(maior[a][0], maior[b][1]),
			maior[a][0] = maior[b][0];
		else maior[a][1] = max(maior[a][1], maior[b][0]);
	}
} dsu;

int a[maxn], b[maxn];

map<int,int> mp;

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &a[i], &b[i]);
		mp[a[i]], mp[b[i]];
	}
	int cnt = 0;
	for(auto& it : mp)
		it.second = cnt++;
	for(int i = 0; i < n; i++) {
		a[i] = mp[a[i]], b[i] = mp[b[i]];
		dsu.join(a[i], b[i]);
	}
	int ans = -1;
	for(int i = 0; i < cnt; i++) {
		if(i != dsu.find(i))
			continue;
		if(dsu.edges[i] > dsu.peso[i]) {puts("-1"); return 0;}
		if(dsu.edges[i] == dsu.peso[i])
			ans = max(ans, dsu.maior[i][0]);
		else ans = max(ans, dsu.maior[i][1]);
	}
	for(auto it : mp)
		if(it.second == ans) {
			ans = it.first; break;
		}
	printf("%d\n", ans);
}