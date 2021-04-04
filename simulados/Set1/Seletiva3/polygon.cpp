#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int deg[maxn], f[maxn], cnt;

bool mark[maxn];

map<string, int> mp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	memset(f, -1, sizeof f);
	int n, ans = 0; cin >> n;
	for(int i = 0; i < n; i++) {
		string s, p; cin >> s >> p;
		if(!mp.count(s)) mp[s] = ++cnt;
		if(!mp.count(p)) mp[p] = ++cnt;
		f[mp[s]] = mp[p];
		++deg[mp[p]];
		if(f[mp[p]] == mp[s] && s != p)
			mark[mp[p]] = mark[mp[s]] = 1; // ja tao no par
	}
	queue<int> q;
	for(int i = 1; i <= n; i++)
		if(!deg[i]) q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop();
		if(mark[u] || mark[f[u]]) continue;
		++ans;
		mark[u] = 1;
		mark[f[u]] = 1;
		--deg[f[u]];
		if(f[u] == f[f[u]]) continue;
		if(!mark[f[f[u]]] && !(--deg[f[f[u]]]))
			q.push(f[f[u]]);
	}
	for(int i = 1; i <= n; i++) {
		if(mark[i]) continue;
		mark[i] = 1;
		int sz = 1, u = f[i];
		while(!mark[u]) ++sz, mark[u] = 1, u = f[u];
		ans += (sz+1)>>1;
	}
	printf("%d\n", n%2?-1:ans);
}