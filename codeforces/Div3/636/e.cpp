#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define deb(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2e5 + 100, inf = 1e9+100;

vi g[maxn];

void bfs(int s, vi &d){
	d[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int now = q.front();
		q.pop();
		for(auto v : g[now]){
			if(d[v] == inf){
				q.push(v);
				d[v] = d[now]+1;
			}
		}
	}
}

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int n, m, a, b, c;
		cin >> n >> m >> a >> b >> c;
		a--, b--, c--;
		vector<int> prices(m);
		vector<ll> pref(m+1);
		for(int i = 0; i < m; i++)
			cin >> prices[i];
		sort(all(prices));
		for(int i = 0; i < m; i++){
			pref[i+1] = pref[i] + prices[i];
		}
		for(int i = 0, x, y; i < m; i++){
			cin >> x >> y;
			x--, y--;
			g[x].pb(y);
			g[y].pb(x);
		}
		vi da(n, inf), db(n, inf), dc(n, inf);
		bfs(a, da);
		bfs(b, db);
		bfs(c, dc);
		ll ans = 1e18+100;
		for(int i = 0; i < n; i++){
			if(da[i] + db[i] + dc[i] > m) continue;
			ans = min(ans, pref[db[i]] + pref[da[i] + db[i] + dc[i]]);
		}
		cout << ans << endl;
		for(int i = 0; i < n; i++)
			g[i].resize(0);
	}
}
