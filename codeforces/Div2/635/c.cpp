#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define pii pair<int, int>
#define piii pair<int ,pii>

struct node{
	int wt, pa, actv=0;
	bool used = false;
	vector<int> adj;
};

const int maxn = 2e5 + 100;

vector<node> g(maxn);
priority_queue<pii> now;

void dfs(int no, int p = -1, int w = 0){
	//cout << "OI" << endl;
	if(g[no].adj.size() == 1 && g[no].adj[0] == p){
		now.push(mp(w, no));
		//cout << "K" << endl;
	}
	g[no].wt = w;
	g[no].pa = p;
	for(auto i : g[no].adj){
		//cout << "KKK" << endl;
		if(i == p) continue;
		dfs(i, no, w+1);
	}
}

void update(int no){
	bool ans = true;
	for(auto i : g[no].adj){
		if(i == g[no].pa) continue;
		if(!g[i].used){
			ans = false;
			break;
		}
	}
	if(ans){
		for(auto i : g[no].adj){
			if(i == g[no].pa) continue;
			g[no].actv += g[i].actv;
		}
		now.push(mp(g[no].wt - g[no].actv, no));
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	for(int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		g[a-1].adj.pb(b-1);
		g[b-1].adj.pb(a-1);
	}
	ll ans = 0;
	dfs(0);
	while(k--){
		pii act = now.top();
		now.pop();
		ans += act.first;
		g[act.second].used = true;
		g[act.second].actv++;
		update(g[act.second].pa);
	}
	cout << ans << endl;
}
