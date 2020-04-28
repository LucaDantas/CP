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

const int maxn = 2e5 + 100;

int pai[maxn];

void init(int n){
	for(int i = 0; i <= n; i++)
		pai[i] = i;
}

int find(int x){
	if(pai[x] == x) return x;
	return find(pai[x]);
}

void join(int x, int y){
	pai[find(x)] = find(y);
}

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int n, k;
		cin >> n >> k;
		init(n);
		for(int i = 1; i <= k; i++){
			for(int j = 1; j < n/k; j++){
				join(i + j*k, i);
			}
		}
		for(int i = 1; i <= n/2; i++)
			join(i, n-i+1);
		string s; cin >> s;
		map<char, int> groups[n+1];
		int ans = 0;
		for(int i = 1; i <= (int)s.size(); i++){
			groups[find(i)][s[i-1]]++;
		}
		for(int i = 1; i <= n; i++){
			int tot = 0;
			int maxcont = 0;
			for(auto x : groups[i]){
				tot += x.s;
				maxcont = max(maxcont, x.s);
			}
			ans += tot - maxcont;
		}
		cout << ans << endl;
		for(int i = 0; i <= n; i++)
			groups[i].clear();
	}
}
