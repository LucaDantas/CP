#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

#define pb push_back
#define pf push_front
#define mp make_pair
#define endl '\n'
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const ll inf = 1e18;
const int MAXM = 10001;
const int MAXG = 1001;

ll dist[MAXM][MAXG];

int main(){
	FAST;
	int n, m;
	cin >> n >> m;
	vll a(m);
	for(int i = 0; i < m; i++){
		cin >> a[i];
	}
	sort(all(a));
	ll g, r; cin >> g >> r;
	
	for(int i = 0; i < MAXM; i++)
		for(int j = 0; j < MAXG; j++)
			dist[i][j] = inf;
	
	deque<pll> q;
	dist[0][0] = 0;
	q.pb({0, 0});
	ll ans = inf;
	while(!q.empty()){
		pll now = q.front();
		q.pop_front();
		ll v = now.first;
		ll mod = now.second;
		if(v == m-1){
			ans = min(ans, dist[v][mod]);
		}
		if(v){
			ll dist_back = a[v] - a[v-1];
			ll next_time = mod + dist_back;
			ll next_mod = next_time%g;
			ll next_dist = dist[v][mod] + dist_back;
			if(next_time <= g){
				if(next_mod == 0) next_dist += r;
				if(dist[v-1][next_mod] > next_dist){
					dist[v-1][next_mod] = next_dist;
					if(next_mod == 0)
						q.pb({v-1, 0});
					else
						q.pf({v-1, next_mod});
				}
			} 
		}
		if(v < m-1){
			ll dist_front = a[v+1] - a[v];
			ll next_time = mod + dist_front;
			ll next_mod = next_time%g;
			if(next_time <= g){
				ll next_dist = dist[v][mod] + dist_front;
				if(next_mod == 0 && v+1 != m-1) next_dist += r;
				if(dist[v+1][next_mod] > next_dist){
					dist[v+1][next_mod] = next_dist;
					if(next_mod == 0)
						q.pb({v+1, 0});
					else
						q.pf({v+1, next_mod});
				}
			} 
		}
	}
	
	if(ans == inf) cout << -1 << endl;
	else cout << ans << endl;
}
