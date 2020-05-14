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

const int maxn = 5e5 + 100;

ll sq[maxn];

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		ll ans = 0;
		for(ll i = 1; i <= n; i+=2){
			ans += ((i-1)>>1)*(i*i - (i-2)*(i-2));
		}
		cout << ans << endl;
	}
}
