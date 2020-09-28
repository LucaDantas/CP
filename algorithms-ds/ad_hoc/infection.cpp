#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e5+10;

vector<int> g[maxn];

int last = -1, a[maxn];

set<int> s;

bool mark[maxn];

int main() {
	int n, m; scanf("%d %d", &n, &m);

	for(int i = 1; i <= m; i++) {
		int u, v; scanf("%d %d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}

	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	s.insert(a[0]);

	for(int i = 1; i <= n; i++) {
		mark[a[i]] = 1;
		s.erase(a[i]);
		for(auto v : g[a[i]])
			if(!mark[v])
				s.insert(v);
		if(i != n && s.upper_bound(a[i+1]) != s.end())
			last = i;
	}

	vector<int> ans;

	s.clear();
	memset(mark, 0, sizeof mark);

	if(last == -1) {
		if(a[1] == n) {printf("-1\n"); return 0;}
		
		s.insert(a[1]+1);
		while(s.size()) {
			int u = *s.begin(); s.erase(s.begin());
			mark[u] = 1;
			for(auto v : g[u])
				if(!mark[v])
					s.insert(v);
			ans.pb(u);
		}
	}
	else {
		for(int i = 1; i <= last; i++) {
			mark[a[i]] = 1; 
			if(s.count(a[i]))
				s.erase(a[i]);
			for(auto v : g[a[i]])
				if(!mark[v])
					s.insert(v);
			ans.pb(a[i]);
		}

		int tam = (int)s.size();

		ans.pb(*s.upper_bound(a[last+1]));

		while(s.size()) {
			s.erase(s.find(ans.back()));
			mark[ans.back()] = 1;
			for(auto v : g[ans.back()])
				if(!mark[v])
					s.insert(v);
			if(s.size())
				ans.pb(*s.begin());
		}
	}


	for(auto it : ans)
		printf("%d ", it);
	printf("\n");
}