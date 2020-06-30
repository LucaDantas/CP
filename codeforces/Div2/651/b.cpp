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
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		vi a(2*n);
		read(a,0,2*n);
		vi par, impar;
		// allin(it, a) {
		// 	if(it%2) impar.pb(it);
		// 	else par.pb(it);
		// }
		rep(i,0,2*n) {
			if(a[i]%2) impar.pb(i+1);
			else par.pb(i+1);
		}
		if(sz(impar)%2) {
			impar.pop_back();
			par.pop_back();
		}
		else {
			if(sz(impar)) impar.pop_back(), impar.pop_back();
			else par.pop_back(), par.pop_back();
		}
		for(int i = 0; i < sz(impar); i += 2) {
			printf("%d %d\n", impar[i], impar[i+1]);
		}
		for(int i = 0; i < sz(par); i += 2) {
			printf("%d %d\n", par[i], par[i+1]);
		}
		// puts("");
	}
}
