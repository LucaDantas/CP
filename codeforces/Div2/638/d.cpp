#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<ll> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;


int main(){
	//FAST;
	int t;
	scanf("%d", &t);
	while(t--){
		int n; scanf("%d", &n);
		vi ans;
		int tot = 1, bac = 1;
		while(true){
			if(n <= tot + bac + bac){
				assert(n >= tot + bac);
				ans.pb(n - (tot+bac));
				break;
			}
			int l = 0, r = bac, best = -1;
			while(l <= r){
				int m = (l+r)>>1;
				int newbac = bac + m;
				if(tot + newbac + newbac > n) r = m-1;
				else { best = m; l = m+1;}
			}
			assert(best != -1);
			ans.pb(best);
			bac += best;
			tot += bac;
		}
		printf("%d\n", sz(ans));
		rep(i, 0, sz(ans)) printf("%lld%c", ans[i], " \n"[i==sz(ans)-1]);
	}
}
