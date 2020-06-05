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

const int maxn = 1e3 + 100;

int grid[maxn][maxn];
bool mark[maxn][maxn];
pii ini, fim;

const pii pos[] = {{1,0},{0,1},{-1,0},{0,-1}};

int dfs(int i, int j) {
	mark[i][j] = 1;
	if(mp(i,j) == fim) return 1;
	int ans = 0x3f3f3f3f;
	rep(k,0,4) {
		if(grid[i+pos[k].ff][j+pos[k].ss] && !mark[i+pos[k].ff][j+pos[k].ss])
			ans = min(ans, dfs(i+pos[k].ff, j+pos[k].ss)+1);
	}
	return ans;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	rep(i,1,n+1) {
		rep(j,1,m+1) {
			scanf("%d", &grid[i][j]);
			if(grid[i][j] == 2) ini = mp(i,j);
			if(grid[i][j] == 3) fim = mp(i,j);
		}
	}
	printf("%d\n", dfs(ini.ff, ini.ss));
}
