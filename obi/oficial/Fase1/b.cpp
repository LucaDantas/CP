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

const int maxn = 600;

char grid[maxn][maxn];

const pii pos[] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int n, f;

bool valid(pii a) {
	int x = a.ff, y = a.ss;
	if(x < 0 || x >= n || y < 0 || y >= n) return false;
	return true;
}

void dfs(int i, int j) {
	grid[i][j] = '*';
	allin(it, pos) {
		pii nxt = mp(i+it.ff, j+it.ss);
		if(!valid(nxt) || grid[nxt.ff][nxt.ss] == '*' || grid[nxt.ff][nxt.ss]-'0' > f) continue;
		dfs(nxt.ff, nxt.ss);
	}
}

int main(){
	cin >> n >> f;
	rep(i,0,n) {
		string linha;
		cin >> linha;
		rep(j,0,n) {
			grid[i][j] = linha[j];
		}
	}

	if(grid[0][0]-'0' <= f)
		dfs(0,0);

	rep(i,0,n) {
		rep(j,0,n) {
			cout << grid[i][j];
		}
		cout << '\n';
	}
}
