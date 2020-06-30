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

const int maxn = 60;

const pii pos[] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
int n, m;

bool valid(int i, int j) {
	return (i >= 0 && i < n && j >= 0 && j < m);
}

bool can[maxn][maxn];

char grid[maxn][maxn];

void dfs(int i, int j) {
	can[i][j] = 1;
	for(pii p : pos) {
		int ni = i+p.ff, nj = j+p.ss;
		if(valid(ni,nj) && can[ni][nj] == 0 && grid[ni][nj] != '#') {
			dfs(ni,nj);
		}
	}
}

int main(){
	int T; cin >> T;
	while(T--) {
		int count_good = 0;
		cin >> n >> m;
		rep(i,0,n) {
			string coluna;
			cin >> coluna;
			rep(j,0,m)
				grid[i][j] = coluna[j];
		}
		rep(i,0,n) rep(j,0,m) count_good += grid[i][j] == 'G';
		if(count_good == 0) {puts("Yes"); continue;}
		rep(i,0,n) {
			rep(j,0,m) {
				if(grid[i][j] == 'B') {
					for(pii p : pos) {
						int ni = i+p.ff, nj = j+p.ss;
						if(valid(ni,nj)) {
							if(grid[ni][nj] == 'G'){ puts("No"); goto done;}
							else if(grid[ni][nj] == '.'){
								grid[ni][nj] = '#';
							}
						}
					}
				}
			}
		}

		clr(can, 0);

		if(grid[n-1][m-1] == '#'){ puts("No"); goto done;}

		dfs(n-1,m-1);

		rep(i,0,n) {
			rep(j,0,m) {
				if(grid[i][j] == 'G' && can[i][j] == 0){ puts("No"); goto done;}
				if(grid[i][j] == 'B') assert(can[i][j] == 0);
			}
		}

		puts("Yes");

		done:
		;
		clr(grid,'#');
	}
}
