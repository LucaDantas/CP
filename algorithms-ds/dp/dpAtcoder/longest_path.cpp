#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e5 + 100;

// In this one we need to do a top sort with bfs and then do a max dp over it

int n, m;

vi g[maxn], top;

int dp[maxn], grau[maxn];

void bfs(){
	queue<int> q;
	
	rep(i,0,n)
		if(grau[i] == 0)
			q.push(i);
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		top.pb(u);
		for(auto v : g[u]){
			grau[v]--;
			if(!grau[v])
				q.push(v);
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	
	rep(i,0,m){
		int u, v; scanf("%d %d", &u, &v);
		u--, v--;
		g[u].pb(v);
		grau[v]++;
	}
	
	bfs();
	
	trav(u, top)
		for(auto v : g[u])
			dp[v] = max(dp[v], dp[u] + 1);
	
	printf("%d\n", *max_element(dp, dp+n));
}
