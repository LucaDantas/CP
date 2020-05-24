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

int main(){
	FAST;
	int T; cin >> T;
	while(T--){
		int n; cin >> n;
		vector<vi> grid(n, vi(n));
		rep(i,0,n){
			string linha; cin >> linha;
			rep(j,0,n)
				grid[i][j] = linha[j] - '0';
		}

		bool broke = false;
		rep(i,0,n-1)
			rep(j,0,n-1){
				if(grid[i][j] && !(grid[i+1][j] || grid[i][j+1])){
					broke = true;
				}
			}
		if(broke) puts("NO");
		else puts("YES");
	}
}
