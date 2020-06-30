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
	while(T--) {
		int n, m, x, y;
		cin >> n >> m >> x >> y;
		ll ans = 0;
		int price1 = x;
		int price2 = min(2*x, y);
		rep(i,0,n) {
			string linha;
			cin >> linha;
			int tam = 0;
			for(auto it : linha) {
				if(it == '*') {
					if(tam&1)
						ans += (tam/2)*price2 + price1;
					else
						ans += (tam/2)*price2;
					tam = 0;
				}
				else
					tam++;
			}
			if(tam&1)
				ans += (tam/2)*price2 + price1;
			else
				ans += (tam/2)*price2;
			tam = 0;
		}
		cout << ans << '\n';
	}
}
