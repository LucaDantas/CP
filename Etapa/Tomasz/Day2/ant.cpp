#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

int n, m, q;

struct Edge {
	int a, b, c;
} edges[maxn];

vector<pair<int,int>> g[maxn];

namespace raiz {

	constexpr int B = 550;

	struct BIT
	{
		int bit[maxn];
		void upd(int x, int v) {
			for(; x < maxn; x += x&-x)
				bit[x] += v;
		}
		int query(int x) {
			int ans = 0;
			for(; x > 0; x -= x&-x)
				ans += bit[x];
			return ans;
		}
		void itv(int l, int r, int v) { upd(l, v); upd(r, -v); }
		void clear() { memset(bit, 0, sizeof bit); }
	} bit[B+5], ans;

	int in[maxn], out[maxn], TT;

	void dfs(int u) {
		in[u] = ++TT;
		for(auto pp : g[u]) { int v = pp.first;
			if(!in[v]) dfs(v);
		}
		out[u] = ++TT;
	}

	set<pair<int,int>> cor[maxn];

	struct Query
	{
		int t, a, b;
	};

	int mp[maxn];

	vector<Query> qr;
	vector<int> cores;

	void limpa() {
		for(int i = 1; i <= m; i++) {
			if(mp[i]) {
				for(auto it : cor[i])
					bit[mp[i]].itv(it.first, it.second, 1);
				continue;
			}
			if(!cor[i].size()) continue;
			auto it = cor[i].begin();
			while(it != cor[i].end()) {
				ans.itv(it->first, it->second, 1);
				it = cor[i].lower_bound({it->second, 0});
			}
		}

		for(auto Q : qr) {
			int t = Q.t;
			if(t == 0) {
				int u = Q.a;
				int aq = ans.query(in[u]);
				for(int c : cores)
					aq += (bit[mp[c]].query(in[u]) > 0);
				printf("%d\n", aq);
			} else {
				int i = Q.a, val = Q.b;
				
				bit[mp[edges[i].c]].itv(in[edges[i].a], out[edges[i].a], -1);
				cor[edges[i].c].erase({in[edges[i].a], out[edges[i].a]});
				
				edges[i].c = val;
				bit[mp[edges[i].c]].itv(in[edges[i].a], out[edges[i].a], 1);

				cor[edges[i].c].insert({in[edges[i].a], out[edges[i].a]});
			}
		}

		qr.clear();
		for(int c : cores) {
			for(auto it : cor[c])
				bit[mp[c]].itv(it.first, it.second, -1);
			mp[c] = 0;
		}
		cores.clear();
		ans.clear();
	}

	void solve() {
		dfs(1);
		for(int i = 1; i < n; i++) {
			if(in[edges[i].a] < in[edges[i].b])
				swap(edges[i].a, edges[i].b);
			cor[edges[i].c].insert({in[edges[i].a], out[edges[i].a]});
		}

		while(q--) {
			char c; scanf(" %c", &c);
			if(c == 'Z') {
				int u; scanf("%d", &u);
				qr.push_back({0, u, 0});
			} else {
				int i, val; scanf("%d %d", &i, &val);
				qr.push_back({1, i, val});
				if(!mp[val]) cores.push_back(val), mp[val] = (int)cores.size();
				val = edges[i].c;
				if(!mp[val]) cores.push_back(val), mp[val] = (int)cores.size();
			}
			if((int)cores.size() >= B) limpa();
		}

		if(qr.size()) limpa();

		exit(0);
	}
};


int main() {
	scanf("%d %d %d", &n, &m, &q);
	bool ok = 1;
	for(int i = 1, a, b, c; i < n; i++)
		scanf("%d %d %d", &a, &b, &c), g[a].pb({b, i}), g[b].pb({a, i}), edges[i] = {a, b, c}, ok &= a==i&&b==i+1;
	raiz::solve();
}