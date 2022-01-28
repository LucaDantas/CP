#pragma GCC optimize("Ofast") 
#pragma GCC optimize("no-stack-protector") 
#pragma GCC optimize("unroll-loops") 

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

constexpr int maxn = 40, tot = 1299600, inf = 0x3f3f3f3f;

vector<int> g[maxn];

int dist[tot][2], coord;

map<long long,int> mp;
long long back[tot];

int get_mp(long long x) { if(mp[x] == 0) mp[x] = ++coord, back[coord] = x; return mp[x]; }

vector<int> get_viz_0(long long atual) {
	vector<int> a, viz;
	for(int i = 0; i < 20; i++)
		if(atual&(1ll<<i)) a.push_back(i);
	for(int u : a)
		for(int v : g[u])
			if(!(atual&(1ll<<(20+v)))) viz.push_back(get_mp(atual^(1ll<<u)^(1ll<<v)));
	return viz; // no max tamanho 60
}

vector<int> get_viz_1(long long atual) {
	vector<int> a, viz;
	for(int i = 0; i < 20; i++)
		if(atual&(1ll<<(i+20))) a.push_back(i);
	for(int u : a)
		for(int v : g[u])
			if(!(atual&(1<<v))) viz.push_back(get_mp(atual^(1ll<<(20+u))^(1ll<<(20+v))));
	return viz; // no max tamanho 60
}

void bfs(int s) {
	queue<pair<int, bool>> q;
	q.push({s, 0});
	q.push({s, 1});
	dist[s][0] = 0;
	dist[s][1] = 0;

	while(q.size()) {
		int u = q.front().first; bool lado = q.front().second; q.pop();

		vector<int> viz = lado ? get_viz_1(back[u]) : get_viz_0(back[u]);

		// db(u, lado, viz);

		for(int v : viz)
			if(dist[v][lado^1] == inf) dist[v][lado^1] = dist[u][lado] + 1, q.push({v, lado^1});
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	string s;
	int tt = 0;
	while(getline(cin, s)) {

		assert(++tt < 50);

		istringstream in(s);
		string ss;
        while(in>>ss)
        {
            for(int i=1; i<ss.size(); i++)
            {
                int u=ss[0]-'a';
					int v=ss[i]-'a';
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }

		// int m2 = maior*maior;
		// int total = min(tot - 10, m2*m2*m2); // maior^6
		int total = tot-10;

		for(int i = 0; i < total; i++)
			dist[i][0] = inf, dist[i][1] = inf;

		int base = (1<<0) | (1<<1) | (1<<2) | (1<<23) | (1<<24) | (1<<25);
		get_mp(base); // base é o 1
		int resp_final = (1<<3) | (1<<4) | (1<<5) | (1<<20) | (1<<21) | (1<<22);
		get_mp(resp_final); // resposta final é 0 2

		bfs(1);

		int ans = min(dist[get_mp(resp_final)][0], dist[get_mp(resp_final)][1]);

		if(ans == inf) puts("No solution.");
		else printf("%d\n", ans);


		for(int i = 0; i < maxn; i++)
			g[i].clear();
		coord = 0;
		mp.clear();
		for(int i = 0; i < total; i++)
			dist[i][0] = 0, dist[i][1] = 0, back[i] = 0;
	}
}
