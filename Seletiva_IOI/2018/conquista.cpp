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
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vi> grid(n,vi(m));
	rep(i,0,n)
		rep(j,0,m)
			scanf("%d", &grid[i][j]);
			
	vector<int> last(m), left(m), right(m);
	last[0] = grid[0][0];
	rep(i,1,m)
		last[i] = last[i-1] + grid[0][i];
	rep(i,1,n) {
		left[0] = last[0] + grid[i][0]; right[m-1] = last[m-1] + grid[i][m-1];
		for(int k = 1; k < m; k++)
			left[k] = max(left[k-1], last[k]) + grid[i][k];
			
		for(int k = m-2; k >= 0; k--)
			right[k] = max(right[k+1], last[k]) + grid[i][k];
		
		rep(k,0,m)
			last[k] = max(left[k], right[k]);
	}
	printf("%d\n", last[m-1]);
}
