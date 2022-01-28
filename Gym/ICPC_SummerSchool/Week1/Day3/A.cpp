#include <bits/stdc++.h>

template <class T = int>
class Dinic {
public:
	struct Edge {
		Edge(int a, T b){to = a;cap = b;}
		int to;
		T cap;
	};

	Dinic(int _n) : n(_n) {
		edges.resize(n);
	}

	T maxFlow(int src, int sink) {
		T ans = 0;
		while(bfs(src, sink)) {
			// maybe random shuffle edges against bad cases?
			T flow;
			pt = std::vector<int>(n, 0);
			while((flow = dfs(src, sink))) {
				ans += flow;
			}
		}
		return ans;
	}

	void addEdge(int from, int to, T cap, T other = 0) {
		edges[from].push_back(list.size());
		list.push_back(Edge(to, cap));
		edges[to].push_back(list.size());
		list.push_back(Edge(from, other));
	}

	bool inCut(int u) const { return h[u] < n; }
	int size() const { return n; }
private:
	int n;
	std::vector<std::vector<int> > edges;
	std::vector<Edge> list;
	std::vector<int> h, pt;

	T dfs(int on, int sink, T flow = 1e9) {
		if(flow == 0) {
			return 0;
		} if(on == sink) {
			return flow;
		}
		for(; pt[on] < (int) edges[on].size(); pt[on]++) {
			int cur = edges[on][pt[on]];
			if(h[on] + 1 != h[list[cur].to]) {
				continue;
			}
			T got = dfs(list[cur].to, sink, std::min(flow, list[cur].cap));
			if(got) {
				list[cur].cap -= got;
				list[cur ^ 1].cap += got;
				return got;
			}
		}
		return 0;
	}

	bool bfs(int src, int sink) {
		h = std::vector<int>(n, n);
		h[src] = 0;
		std::queue<int> q;
		q.push(src);
		while(!q.empty()) {
			int on = q.front();
			q.pop();
			for(auto a : edges[on]) {
				if(list[a].cap == 0) {
					continue;
				}
				int to = list[a].to;
				if(h[to] > h[on] + 1) {
					h[to] = h[on] + 1;
					q.push(to);
				}
			}
		}
		return h[sink] < n;
	}
};

struct Edge {
	int x, y, w;
	bool operator<(Edge a) {
		return w < a.w;
	}
};

std::vector<Edge> edges;

int bs(int n, int k) {
	int l = 1, r = 100000, ans = -1;

	while(l <= r) {
		int m = (l+r) >> 1;

		Dinic<int> F((n+2) << 1);

		for(int i = 0; i <= n+1; i++)
			F.addEdge(i, i+n+2, 1);

		for(Edge e : edges) {
			if(e.w > m) continue;
			F.addEdge(e.x + n+2, e.y, 1);
		}

		if(F.maxFlow(n+2, n+1) >= k) ans = m, r = m-1;
		else l = m+1;
	}

	return ans;
}

int main() {
	int tt = 0;
	int n; scanf("%d", &n);
	while(n) {
		++tt;
		edges.clear();
		int T; scanf("%d", &T);
		for(int i = 0; i < T; i++) {
			int x, y, w; scanf("%d %d %d", &x, &y, &w);
			if(x > y) std::swap(x, y);
			edges.push_back({x, y, w});
		}
		int k; scanf("%d", &k);
		printf("Case %d: ", tt);
		int ans = bs(n, k);
		if(ans == -1) puts("no solution");
		else printf("%d\n", ans);
		scanf("%d", &n);
	}
}
