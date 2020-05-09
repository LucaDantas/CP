#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 1e5 + 100;

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vi pref(n+1), a(n+1);
		bool can[n+1];
		clr(can, 0);
		for(int i = 1; i <= n; i++){
			int v; cin >> v;
			a[i] = v;
			pref[i] = pref[i-1] + v;
		}
		for(int i = 1; i <= n; i++)
			for(int j = i+1; j <= n; j++){
				int now = pref[j] - pref[i-1];
				if(now <= n){
					can[now] = true;
					//db(now);
				}
			}
		int ans = 0;
		for(int i = 1; i <= n; i++)
			if(can[a[i]]) ans++;
		cout << ans << endl;
	}
}
