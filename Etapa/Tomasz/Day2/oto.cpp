#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 2e5+10;

int n, m, q;

struct Edge {
	int a, b, c;
} edges[maxn];

vector<pair<int,int>> g[maxn];

namespace slow {

	pair<int,int> pai[maxn];

	void dfs(int u, int p = 0) {
		for(auto pp : g[u]) {
			int v = pp.first, id = pp.second;
			if(v != p) dfs(v, u), pai[v] = {u, id};
		}
	}

	int cnt[maxn], ans;

	vector<int> cores;

	void get(int u) {
		while(u != 1) {
			cores.pb(edges[pai[u].second].c);
			u = pai[u].first;
		}
		ans = 0;
		for(int x : cores)
			if(!cnt[x]) ++ans, cnt[x] = 1;
		for(int x : cores)
			cnt[x] = 0;
		cores.clear();
	}

	void solve() {
		dfs(1);

		while(q--) {
			char c; scanf(" %c", &c);
			if(c == 'Z') {
				int u; scanf("%d", &u);
				get(u);
				printf("%d\n", ans);
			} else {
				int i, val; scanf("%d %d", &i, &val);
				edges[i].c = val;
			}
		}

		exit(0);
	}
};

namespace linha {

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
	} bit;

	int in[maxn], out[maxn], t;

	void dfs(int u) {
		in[u] = ++t;
		for(auto pp : g[u]) { int v = pp.first;
			if(!in[v]) dfs(v);
		}
		out[u] = ++t;
	}

	set<pair<int,int>> st[maxn];

	void add(int cor, pair<int,int> itv) {
		auto it = st[cor].lower_bound(itv);
		if(it == st[cor].begin() || prev(it)->second < itv.first) {
			bit.itv(itv.first, itv.second, 1);
			if(it != st[cor].end() && it->second < itv.second)
				bit.itv(it->first, it->second, -1);
		}
		st[cor].insert(itv);
	}

	void rmv(int cor, pair<int,int> itv) {
		auto it = st[cor].find(itv);
		if(it == st[cor].begin() || prev(it)->second < itv.first) {
			bit.itv(itv.first, itv.second, -1);
			if(next(it) != st[cor].end() && next(it)->second < itv.second)
				bit.itv(next(it)->first, next(it)->second, 1);
		}
		st[cor].erase(it);
	}

	void solve() {
		dfs(1);
		for(int i = 1; i < n; i++) {
			if(in[edges[i].a] < in[edges[i].b])
				swap(edges[i].a, edges[i].b);
			add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
		}

		while(q--) {
			char c; scanf(" %c", &c);
			if(c == 'Z') {
				int u; scanf("%d", &u);
				printf("%d\n", bit.query(in[u]));
			} else {
				int i, val; scanf("%d %d", &i, &val);
				rmv(edges[i].c, {in[edges[i].a], out[edges[i].a]});
				edges[i].c = val;
				add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
			}
		}

		// fprintf(stderr, "OI");

		exit(0);
	}

};

namespace pequeno {

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
	} bit[20];

	int in[maxn], out[maxn], t;

	void dfs(int u) {
		in[u] = ++t;
		for(auto pp : g[u]) { int v = pp.first;
			if(!in[v]) dfs(v);
		}
		out[u] = ++t;
	}

	void add(int c, pair<int,int> itv) { bit[c].itv(itv.first, itv.second, 1); }
	void rmv(int c, pair<int,int> itv) { bit[c].itv(itv.first, itv.second, -1); }

	void solve() {
		dfs(1);
		for(int i = 1; i < n; i++) {
			if(in[edges[i].a] < in[edges[i].b])
				swap(edges[i].a, edges[i].b);
			add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
		}

		while(q--) {
			char c; scanf(" %c", &c);
			if(c == 'Z') {
				int u, ans = 0; scanf("%d", &u);
				for(int i = 1; i <= m; i++)
					ans += bit[i].query(in[u]) > 0;
				printf("%d\n", ans);
			} else {
				int i, val; scanf("%d %d", &i, &val);
				rmv(edges[i].c, {in[edges[i].a], out[edges[i].a]});
				edges[i].c = val;
				add(edges[i].c, {in[edges[i].a], out[edges[i].a]});
			}
		}

		exit(0);
	}
};


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
	if(ok) linha::solve();
	if(m <= 15) pequeno::solve();
	if(n <= 2000 && q <= 2000) slow::solve();
	raiz::solve();
}
