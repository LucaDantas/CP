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
		int n;
		scanf("%d", &n);
		vi a(n);
		read(a,0,n);
		vi ans;
		ans.pb(a[0]);
		bool up = a[1] > a[0];
		for(int i = 1; i < n-1; i++) {
			if(up && a[i] > a[i+1]) {
				up = false;
				ans.pb(a[i]);
			}
			else if(!up && a[i] < a[i+1]) {
				up = true;
				ans.pb(a[i]);
			}
		}
		ans.pb(a.back());
		printf("%d\n", sz(ans));
		rep(i,0,sz(ans)) printf("%d%c", ans[i], " \n"[i==sz(ans)-1]);
	}
}
