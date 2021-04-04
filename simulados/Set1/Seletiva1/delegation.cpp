#include<cstdio>
#include<vector>
#include<set>
using namespace std;

#define pb push_back

constexpr int maxn = 1e5+10;

FILE *in, *out;

int K, ok;

vector<int> g[maxn];

int dfs(int u, int p) {
	if(g[u].size() == 1 && g[u][0] == p) return 1;
	multiset<int> tam; int cnt = 0;
	for(int v : g[u]) {
		if(v != p) {
			int x = dfs(v, u);
			if(!ok) return -1;
			if(x >= K) ++cnt;
			else tam.insert(x);
		}
	}
	multiset<int> sv = tam;
	int sv_cnt = cnt;

	int passar = -1;
	for(int lim = 0; lim <= min(cnt, 1); lim++) {
		vector<int> sobrou;
		while(tam.size() && cnt > lim) {
			tam.erase(tam.begin());
			--cnt;
		}
		while(tam.size()) {
			auto x = tam.begin(); int val = *x;
			tam.erase(x);
			auto y = tam.lower_bound(K-val);
			if(y == tam.end()) sobrou.pb(val);
			else tam.erase(y);
		}
		if(cnt > (int)sobrou.size()) passar = K;
		else if(cnt+1 >= (int)sobrou.size() && sobrou.size() > 0)
			passar = max(passar, sobrou.back()+1);
		else if(!sobrou.size()) passar = 1;
		tam = sv;
		cnt = sv_cnt;
	}
	if(passar == -1) ok = 0;
	return passar;
}

void get() {
	multiset<int> tam;
	vector<int> sobrou;
	for(int v : g[1])
		tam.insert(dfs(v, 1));
	while(tam.size()) {
		auto x = tam.begin(); int val = *x;
		tam.erase(x);
		auto y = tam.lower_bound(K-val);
		if(y == tam.end()) sobrou.pb(val);
		else tam.erase(y);
	}
	if(sobrou.size() && sobrou.front() < K) ok = 0;
}

int main() {
	in = fopen("deleg.in", "r");
	out = fopen("deleg.out", "w");

	int n; fscanf(in, "%d", &n);
	for(int i = 1, a, b; i < n; i++)
		fscanf(in, "%d %d", &a, &b), g[a].pb(b), g[b].pb(a);
	int l = 1, r = n, ans = -1;
	while(l <= r) {
		K = (l+r) >> 1;
		ok = 1;
		get();
		if(ok) ans = K, l = K+1;
		else r = K-1;
	}
	fprintf(out, "%d\n", ans);
}