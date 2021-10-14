#include <bits/stdc++.h>
#include "lib/tree.hpp"
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

constexpr int n = 5e6, B = 31 - __builtin_clz(n) + 2, maxn = n + 10, lim = B / (31 - __builtin_clz(B));

vector<int> g[maxn];
int dp[maxn], mark[B];

void dfs(int u, int p = 0) {
	int peq = 0;
	for(int v : g[u])
		if(v != p) dfs(v, u), peq += (dp[v] < B);
	static vector<int> aq; aq.clear();
	for(int v : g[u]) {
		if(v == p) continue;
		if(peq > lim && dp[v] < B) ++mark[dp[v]];
		else aq.push_back(dp[v]);
	}
	sort(aq.begin(), aq.end(), greater<int>());
	if(peq > lim) for(int i = B-1; i >= 0; i--)
		while(mark[i]) aq.push_back(i), --mark[i];
	reverse(aq.begin(), aq.end());
	for(int i = 0; i < (int)aq.size(); i++)
		aq[i] += i+1, dp[u] = max(dp[u], aq[i]);
}

void lento(int u, int p = 0) {
	for(int v : g[u])
		if(v != p) lento(v, u);
	static vector<int> aq; aq.clear();
	for(int v : g[u]) {
		if(v == p) continue;
		aq.push_back(dp[v]);
	}
	sort(aq.begin(), aq.end());
	for(int i = 0; i < (int)aq.size(); i++)
		aq[i] += i+1, dp[u] = max(dp[u], aq[i]);
}


int main() {
	libgen::Tree t;
	t.generate_prufer(n, rng);
	for(const auto& p : t)
		g[p.first].push_back(p.second), g[p.second].push_back(p.first);
	dfs(1);
	// lento(1);
	printf("%d\n", dp[1]);
}
