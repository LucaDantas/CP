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

const int maxn = 110;

int n, k;

inline int dist(int x1, int y1, int x2, int y2) {
	return abs(x1-x2) + abs(y1-y2);
}

struct mapa {
	int grid[maxn][maxn];
	
	void init() {
		clr(grid, 0);
	}
	
	void criar(int x, int y, int d) {
		clr(grid, 0);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(dist(x,y,i,j) == d) {
					grid[i][j] = 1;
				}
			}
		}
	}
	//void show() {
		//for(int i = 0; i < n; i++) {
			//for(int j = 0; j < n; j++) {
				//printf("%d%c", grid[i][j], " \n"[j==n-1]);
			//}
		//}
	//}
	pii find() {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(grid[i][j])
					return mp(i,j);
			}
		}
		return mp(-1, -1);
	}
	
	int count() {
		int ret = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(grid[i][j])
					ret++;
			}
		}
		return ret;
	}
};

mapa compara(mapa a, mapa b) {
	mapa ret;
	ret.init();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			ret.grid[i][j] = a.grid[i][j] && b.grid[i][j];
		}
	}
	return ret;
}

int main(){
	scanf("%d %d", &n, &k);
	mapa mps[k];
	
	for(int i = 0; i < k; i++) {
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		mps[i].criar(x, y, d);
	}

	mapa resp = mps[0];
	for (int i = 1; i < k; i++) {
		resp = compara(resp, mps[i]);
	}

	if(resp.count() > 1) {
		printf("-1 -1\n");
		return 0;
	}
	pii ans = resp.find();
	printf("%d %d\n", ans.ff, ans.ss);
}
