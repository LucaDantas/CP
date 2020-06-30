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
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<
 
int main(){
	int t; scanf("%d", &t);
	while(t--) {
		int d, m;
		ll ans = 1;
		scanf("%d %d", &d, &m);
		for(int i = 0; i < 30; i++) {
			if(d < (1 << i)) break;
			ans *= (min((1 << (i+1)) - 1,d) - (1 << i) + 2) % m;
			ans %= m;
		}
		ans--;
		if(ans < 0) ans += m;
		printf("%d\n", ans);
	}
}
