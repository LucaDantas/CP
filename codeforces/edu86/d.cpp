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
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;
vi m, c, lim, nums;

int main(){
	FAST;
	int n, k;
	cin >> n >> k;
	nums.resize(k+1);
	lim.resize(k+1);
	m.resize(n+1);
	c.resize(k+1);
	for(int i = 1; i <= n; i++)
		cin >> m[i];
	for(int i = 1; i <= k; i++)
		cin >> c[i];
	lim[1] = c[0];
	for(int i = 2; i <= k; i++)
		lim[i] = min(lim[i-1], c[i]);
	for(int i = 1; i <= n; i++)
		nums[it]++; 
	
}
