#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e3+10;

vector<int> g[maxn], massa;

void get_dist(int u, int p, int d) {
	if(!d) return (void)(massa.push_back(u));
	for(int v : g[u])
		if(v != p) get_dist(v, u, d-1);
}

pair<int,int> query(vector<int> ask) {
	printf("? %ld", ask.size());
	for(int x : ask) printf(" %d", x);
	printf("\n"); fflush(stdout);
	pair<int,int> ans; scanf("%d %d", &ans.first, &ans.second);
	return ans;
}

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			g[i].clear();

		for(int i = 1, a, b; i < n; i++)
			scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
		
		vector<int> a(n); iota(a.begin(), a.end(), 1);
		pair<int,int> qr = query(a);
		int c = qr.first, dist = qr.second;

		int l = (dist+1)/2, r = dist, bom = c;
		while(l <= r) {
			int m = (l+r) >> 1;
			massa.clear();
			get_dist(c, 0, m);
			if(!massa.size()) {r = m-1; continue;}
			qr = query(massa);
			if(qr.second == dist) {
				bom = qr.first;
				l = m+1;
			} else r = m-1;
		}

		massa.clear();
		get_dist(bom, 0, dist);

		printf("! %d %d\n", bom, query(massa).first); fflush(stdout);
		char s[20];
		scanf("%s", s);
	}
}