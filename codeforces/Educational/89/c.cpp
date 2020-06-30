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

int main(){
	int t; scanf("%d", &t);
	while(t--) {		
		int n, m, ans=0;
		scanf("%d %d", &n, &m);
		
		vector<vi> grid(n, vi(m));

		vector<vi> cnt(n+m, vi(2));
		
		rep(i,0,n) rep(j,0,m) scanf("%d", &grid[i][j]);

		rep(i,0,n) rep(j,0,m) cnt[i+j][grid[i][j]]++;

		for(int i = 0; i <= (n+m-3)/2; i++) ans += min(cnt[i][0] + cnt[n+m-2-i][0], cnt[i][1] + cnt[n+m-2-i][1]);
		printf("%d\n", ans);
	}
}
