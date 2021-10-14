#include <bits/stdc++.h>
using namespace std;

namespace libgen {
	template <typename T, typename Enable = void>
	class randomizer;

	template <typename T>
	class randomizer<T, typename
	    std::enable_if<std::is_floating_point<T>::value>::type> {
	public:
	    randomizer(T min, T max) : _rng(min, max) {  }

	    template <typename Generator>
	    T operator()(Generator& gen) {
	        return _rng(gen);
	    }

	private:
	    std::uniform_real_distribution<T> _rng;
	};

	template <typename T>
	class randomizer<T, typename
	    std::enable_if<std::is_integral<T>::value>::type> {
	public:
	    randomizer(T min, T max) : _rng(min, max) {  }

	    template <typename Generator>
	    T operator()(Generator& gen) {
	        return _rng(gen);
	    }

	private:
	    std::uniform_int_distribution<T> _rng;
	};

	template<typename T, typename Randomizer = randomizer<T>>
	class vector : public std::vector<T> {
	public:
	    template<typename Generator>
	    void generate(int n, std::pair<T, T> const& range, Generator& gen) {
	        Randomizer rng(range.first, range.second);

	        this->resize(n);

	        for (int i = 0; i < n; i++)
	            (*this)[i] = rng(gen);
	    }

	    template<typename Generator>
	    void permutation(int n, int b, Generator& gen) {
	        this->resize(n);
	        std::iota(this->begin(), this->end(), b);
	        std::shuffle(this->begin(), this->end(), gen);
	    }

	    friend std::ostream& operator<<(std::ostream& os, libgen::vector<T> const& V) {
	        for(const T& x : V)
	            os << x << ' ';
	        return os;
	    }
	    
	    void operator=(const std::vector<T>& v) {
	        this->resize(v.size());
	        for(std::size_t i = 0; i < v.size(); i++)
	            (*this)[i] = v[i];
	    }
	private:
	};


	class Tree : public std::vector<std::pair<int,int>> {
	public:
	    template <typename Generator>
	    void generate_prufer(int n, Generator& gen, int index = 1) {
	        if(n == 1) return;
	        this->resize(n-1);
	        
	        libgen::vector<int> prufer;
	        prufer.generate(n-2, {0, n-1}, gen);

	        std::vector<int> degree(n, 1);
	        
	        for(int x : prufer)
	            ++degree[x];

	        int ptr = 0, leaf;
	        while(degree[ptr] != 1) ++ptr;
	        leaf = ptr;

	        for(int i = 0; i < n-2; i++) {
	            (*this)[i] = std::pair<int,int>(leaf, prufer[i]);
	            --degree[leaf];
	            if(--degree[prufer[i]] == 1 && prufer[i] < ptr) leaf = prufer[i];
	            else { while(degree[ptr] != 1) ++ptr; leaf = ptr; }
	        }

	        (*this)[n-2] = std::pair<int,int>(leaf, n-1);

	        for(int i = 0; i < n-1; i++)
	            (*this)[i].first += index, (*this)[i].second += index;

	        std::shuffle(this->begin(), this->end(), gen);
	    }

	    template<typename Generator>
	    void generate_blocks(int n, int group_size, Generator& gen, int index = 1) {
	        std::vector<std::vector<int>> block;
	        libgen::randomizer<int> rng(1, group_size);

	        libgen::vector<int> ind;
	        ind.permutation(n, 0, gen);

	        this->resize(n-1);
	        int pos = 0;
	        for(int i = 0, sz = 0; sz < n; i++) {
	            int b = std::min(n - sz, rng(gen));
	            std::vector<int> here = {ind[sz]};
	            for(int j = 1; j < b; j++) {
	                here.push_back(ind[sz + j]);
	                (*this)[pos++] = {ind[sz + j], ind[sz]};
	            }
	            block.push_back(here);
	            sz += b;
	        }

	        Tree t;
	        t.generate_prufer((int)block.size(), gen, 0);

	        // It is too expensive to declare a libgen::randomizer<int> every time
	        auto rnd = [&gen](int aaa) { return (int)(gen() % aaa + aaa) % aaa; };
	        for(std::pair<int,int> p : t)
	            (*this)[pos++] = {block[p.first][rnd((int)block[p.first].size())], block[p.second][rnd((int)block[p.second].size())]};

	        for(int i = 0; i < n-1; i++)
	            (*this)[i].first += index, (*this)[i].second += index;

	        std::shuffle(this->begin(), this->end(), gen);
	    }
	private:
	};

};

#define pb push_back

constexpr int maxn = 2e5+10;

int n, m, q;

struct Edge {
	int a, b, c;
} edges[maxn];

vector<pair<int,int>> g[maxn];

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));
std::mt19937_64 rng64(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  if constexpr(sizeof(T) <= 32) k = (T) rng(); else k = (T) rng64();
  return (T) (((k % v) + v) % v);
}

template<typename T> T rnd(T l, T r) {
  if (r < l) swap(l, r);
  return (T) (l + rnd(r - l + 1));
}

namespace raiz {

	constexpr int B = 500;

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
			// char c; scanf(" %c", &c);
			// if(c == 'Z') {
			if(rnd(2)) {
				// int u; scanf("%d", &u);
				int u = rnd(1, n);
				qr.push_back({0, u, 0});
			} else {
				// int i, val; scanf("%d %d", &i, &val);
				int i = rnd(1, n), val = rnd(1, m);
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
	// scanf("%d %d %d", &n, &m, &q);
	n = 100000, m = 150000, q = 150000;
	libgen::Tree tree;
	tree.generate_blocks(n, 100, rng);
	for(int i = 1, a, b, c; i < n; i++) {
		a = tree[i-1].first, b = tree[i-1].second, c = rnd(1, m);
		g[a].pb({b, i}), g[b].pb({a, i}), edges[i] = {a, b, c};
	}
	raiz::solve();
}