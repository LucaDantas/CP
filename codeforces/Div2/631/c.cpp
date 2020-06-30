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
#define int long long

const int maxn = 1e5 + 100;

int32_t main(){
	FAST;
	int n, m;
	bool bad = false;
	cin >> n >> m;
	vector<ll> a(m);
	for(int i = 0; i < m; i++){
		cin >> a[i];
		if(a[i] + i > n) bad = true;
	}
	if(accumulate(all(a), 0LL) < n || bad){
		cout << -1 << endl;
		return 0;
	}
	int diff = n-m, pos=n;
	vector<ll> ans;
	for(int i = m-1; i >= 0; i--){
		pos--;
		if(diff > 0){
			if(a[i] <= diff){
				pos -= a[i]-1;
				diff -= a[i]-1;
			}
			else if(a[i] > diff){
				pos -= diff;
				diff=0;
			}
		}
		ans.pb(pos+1);
	}
	reverse(all(ans));
	for(auto it : ans) cout << it << ' ';
	cout << '\n';
}
