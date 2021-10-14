#ifndef _LIBGEN_RANDOMIZER_HPP
#define _LIBGEN_RANDOMIZER_HPP

#include <type_traits>
#include <random>

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

}

#endif

#ifndef _LIBGEN_VECTOR_HPP
#define _LIBGEN_VECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>

namespace libgen {

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

}

#endif

#ifndef _LIBGEN_TREE_HPP
#define _LIBGEN_TREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>

namespace libgen {

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
        auto rnd = [&gen](int m) { return (int)(gen() % m + m) % m; };
        for(std::pair<int,int> p : t)
            (*this)[pos++] = {block[p.first][rnd((int)block[p.first].size())], block[p.second][rnd((int)block[p.second].size())]};

        for(int i = 0; i < n-1; i++)
            (*this)[i].first += index, (*this)[i].second += index;

        std::shuffle(this->begin(), this->end(), gen);
    }
private:
};

template <typename T = int, typename Randomizer = randomizer<T>>
class WeightedTree : public std::vector<std::pair<std::pair<int, int>, T>> {
public:
    template <typename Generator>
    void generate_prufer(int n, std::pair<T, T> const& range, Generator& gen, int index = 1) {
        if(n == 1) return;
        t.generate_prufer(n, gen, index);
        set(range, gen);
    }

    template <typename Generator>
    void generate_blocks(int n, int group_size, std::pair<T, T> const& range, Generator& gen, int index = 1) {
        if(n == 1) return;
        t.generate_blocks(n, group_size, gen, index);
        set(range, gen);
    }

private:
    Tree t;
    
    template <typename Generator>
    void set(std::pair<T, T> const& range, Generator& gen) {
        Randomizer rng(range.first, range.second);

        this->resize(t.size());

        for(std::size_t i = 0; i < t.size(); i++)
            (*this)[i] = {t[i], rng(gen)};

        t.clear();
    }
};

}

#endif




#include <bits/stdc++.h>
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '['; string sep = ""; for (const auto &x : v) os << sep << x, sep = ", "; return os << ']'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A> ostream& operator<<(ostream &os, const set<A> &s) { os << '{'; string sep = ""; for (const auto &x : s) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const map<A, B> &m) { os << '{'; string sep = ""; for (const auto &x : m) os << sep << x.first << " -> " << x.second, sep = ", "; return os << '}'; }

#ifdef MY_DEBUG_FLAG
void debug() { cerr << endl; }
template<typename Ini, typename... Fim> void debug(Ini I, Fim... F) { cerr << I; if(sizeof...(F)) cerr << ", "; debug(F...);}
#define db(...) cerr << "DEBUG (" << #__VA_ARGS__ << ") == ", debug(__VA_ARGS__)
#else
#define db(...)
#endif

mt19937 rng(random_device{}());

int rnd(int x) { return (int)(rng() % x + x) % x; }
int rnd(int l, int r) { return l + rnd(r-l+1); }

// constexpr int n = 1e7, B = 31 - __builtin_clz(n) + 2, maxn = n + 10, lim = B / (31 - __builtin_clz(B));
constexpr int n = 1e6, B = 30+1, maxn = n + 10, lim = 8;


vector<int> g[maxn];
int dp[maxn], mark[B];

void dfs(int u, int p = 0) {
	int mx = 0;
	for(int v : g[u]) {
		if(v != p) dfs(v, u);
		if(dp[v] < B) mx = max(mx, dp[v]);
	}
	static vector<int> aq; aq.clear();
	for(int v : g[u]) {
		if(v == p) continue;
		if(dp[v] < B) ++mark[dp[v]];
		else aq.push_back(dp[v]);
	}
	for(int i = mx; i >= 0; i--)
		while(mark[i]) aq.push_back(i), --mark[i];
	for(int i = 0; i < (int)aq.size(); i++)
		aq[i] += i+1, dp[u] = max(dp[u], aq[i]);
}


/* void dfs(int u, int p = 0) {
	int peq = 0;
	for(int v : g[u])
		if(v != p) dfs(v, u), peq += (dp[v] < B);
	static vector<int> aq; aq.clear();
	for(int v : g[u]) {
		if(v == p) continue;
		if(peq > lim && dp[v] < B) ++mark[dp[v]];
		else aq.push_back(dp[v]);
	}
	// sort(aq.begin(), aq.end(), greater<int>());
	if(peq > lim) for(int i = B-1; i >= 0; i--)
		while(mark[i]) aq.push_back(i), --mark[i];
	reverse(aq.begin(), aq.end());
	for(int i = 0; i < (int)aq.size(); i++)
		aq[i] += i+1, dp[u] = max(dp[u], aq[i]);
} */

vector<pair<int,int>> st;

void lento(int u, int p = 0) {
	static vector<int> aq; aq.clear();
	for(int v : g[u]) if(v != p)
		aq.push_back(dp[v]);
	// sort(aq.begin(), aq.end());
	for(int i = 0; i < (int)aq.size(); i++)
		aq[i] += i+1, dp[u] = max(dp[u], aq[i]);
}

void visit(int k) {
	st.emplace_back(k, 0);
	while(st.size()) {
		auto [u, p] = st.back(); st.pop_back();
		lento(u, p);
	}
}

int sz = n, t = 0;

void add() { int a = rnd(1, sz); ++sz; g[a].push_back(sz), g[sz].push_back(a); }

void pre(int u, int p) { int eu = t; for(int& v : g[u]) if(v != p) {int sv = ++t; pre(v, u), v = sv;} }

int main() {
	libgen::Tree tree;
	// tree.generate_blocks(n, 5000, rng);
	tree.generate_prufer(n, rng);
	for(const auto& p : tree)
		g[p.first].push_back(p.second), g[p.second].push_back(p.first);
	pre(1, 0);
	for(int i = 0; i < qtd; i++) {
		// visit(1);
		// dfs(rnd(1, sz));
		// visit(rnd(1, sz));
		// for(int x = 0; x < qtd_add; x++) add();
		// memset(dp, 0, sizeof dp);
	}
}

