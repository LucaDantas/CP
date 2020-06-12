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

const int maxn = 550;

int n, m;

char grid[maxn][maxn];

bool mark[maxn][maxn];

bool valid(int a, int b) {
	if(a < 0 || a >= n || b < 0 || b >= m) return false;
	return true;
}

void dfs(int i, int j) {
	if(!valid(i,j) || mark[i][j]) return;
	mark[i][j] = 1;
	grid[i][j] = 'o';
	if(i+1 < n && grid[i+1][j] == '#') dfs(i,j+1), dfs(i, j-1);
	else if(i+1 < n && grid[i+1][j] == '.') dfs(i+1, j);
}

int main(){
	FAST;
	cin >> n >> m;
	rep(i,0,n) {
		string linha; cin >> linha;
		rep(j,0,m) grid[i][j] = linha[j];
	}
	int ini = 0;
	rep(i,0,m) if(grid[0][i] == 'o') ini = i;
	dfs(0,ini);
	rep(i,0,n) { rep(j,0,m) cout << grid[i][j]; cout << '\n';}
}
