#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(a) a.begin(), a.end()

constexpr int maxn = 1e5+10;

int a[maxn][10], back[maxn][10];

struct DSU
{
	int pai[maxn], sz[maxn];
	DSU() {for(int i = 0; i < maxn; i++) pai[i] = i, sz[i] = 1;}
	int find(int x) {return pai[x]==x?x:pai[x]=find(pai[x]);}
	void join(int x, int y) {
		x = find(x), y = find(y);
		if(x == y) return;
		if(a[x][0] < a[y][0]) swap(x, y);
		pai[y] = x; sz[x] += sz[y];
	}
} dsu;

set<int> st, ord[10];

void liga(int p, int eu) {
	vector<int> rm;
	for(auto it = st.find(a[eu][0]); it != st.end() && back[*it][0] != p; ++it) {
		dsu.join(p, back[*it][0]);
		rm.pb(back[*it][0]);
	}
	for(int x : rm)
		st.erase(a[x][0]);
}

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < k; j++)
			scanf("%d", &a[i][j]);
	}

	for(int j = 0; j < k; j++) {
		map<int, int> mp;
		for(int i = 0; i < n; i++)
			mp[a[i][j]];
		int aux = 0;
		for(auto& it : mp)
			it.second = ++aux;
		for(int i = 0; i < n; i++)
			a[i][j] = mp[a[i][j]], back[a[i][j]][j] = i;
	}

	for(int i = 0; i < n; i++) {
		auto it = st.insert(a[i][0]).first;
		auto it2 = ord[0].insert(a[i][0]).first;

		if(it2 != ord[0].begin() && next(it) != st.end() &&
			dsu.find(back[*prev(it2)][0]) == back[*next(it)][0])
				dsu.join(back[*next(it)][0], i), st.erase(it);

		for(int j = 1; j < k; j++) {
			it2 = ord[j].insert(a[i][j]).first;

			if(it2 != ord[j].begin()) {
				int p = dsu.find(back[*prev(it2)][j]), eu = dsu.find(i);
				if(a[p][0] > a[eu][0])
					liga(p, eu);
			}

			if(next(it2) != ord[j].end()) {
				int p = dsu.find(i), eu = dsu.find(back[*next(it2)][j]);
				if(a[p][0] > a[eu][0])
					liga(p, eu);
			}
		}
		printf("%d\n", dsu.sz[back[*st.rbegin()][0]]);
	}
}