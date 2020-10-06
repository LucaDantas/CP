#include<bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

#define pb push_back
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)((a).size())

constexpr int maxn = 1e5+10;

vector<int> topo;
vector<vector<pii>> pilha;

int ans[maxn];

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n);
	for(auto& it : a)
		scanf("%d", &it);
	for(int i = 0; i < n; i++) {
		auto it = lower_bound(all(topo), a[i]);
		if(it == topo.end())
			topo.pb(a[i]), pilha.pb({{a[i], i}});
		else {
			int pos = (int)(it - topo.begin());
			topo[pos] = a[i];
			pilha[pos].pb({a[i], i}); 
		}
	}

	vector<pii> valid = pilha.back();
	if(sz(valid) > 1)
		for(auto it : valid)
			ans[it.second] = 2;
	else
		ans[valid[0].second] = 3;

	for(int i = sz(pilha)-2; i >= 0; i--) {
		sort(all(valid));
		vector<int> suf(sz(valid)), comp(sz(valid));
		suf.back() = valid.back().second;
		for(int pos = sz(valid)-2; pos >= 0; pos--)
			suf[pos] = max(suf[pos+1], valid[pos].second);
		for(int j = 0; j < sz(valid); j++)
			comp[j] = valid[j].first;
		valid.clear(); // já limpei pra começar a encher com os caras de agora
		
		for(int j = 0; j < sz(pilha[i]); j++) { 
			auto it = upper_bound(all(comp), pilha[i][j].first);
			if(it == comp.end())
				ans[pilha[i][j].second] = 1;
			else {
				int pos = (int)(it - comp.begin());
				if(suf[pos] < pilha[i][j].second)
					ans[pilha[i][j].second] = 1;
				else
					valid.pb(pilha[i][j]);
			}
		}

		if(sz(valid) > 1)
			for(auto it : valid)
				ans[it.second] = 2;
		else
			ans[valid[0].second] = 3;
	}

	for(int i = 0; i < n; i++)
		printf("%d", ans[i]);
	printf("\n");
}