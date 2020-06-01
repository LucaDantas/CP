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

vector<vi> s;

int query(const vi& ind) {
	cout << "? ";
	cout << sz(ind);
	allin(it, ind) {
		cout << ' ' << it;
	}
	cout << endl;
	int val;
	cin >> val;
	return val;
}

vi complement(vi v, int n){
	vi ask, occur(n + 1);
	for(int i : v)
		occur[i] = 1;
	for(int i = 1; i <= n; i++)
		if(!occur[i])
			ask.push_back(i);
	return ask;
}

int main(){
	int t; cin >> t;
	while(t--) {
		
		int n, k; cin >> n >> k;
		s.resize(k);
		
		rep(i,0,k) {
			int sz; cin >> sz;
			s[i].resize(sz);
			rep(j,0,sz)
				cin >> s[i][j];
		}
		
		vi ask;
		
		rep(i,1,n+1)
			ask.pb(i);
		
		int mx = query(ask);
		
		int l = 0, r = k-1;
		
		while(l < r) {
			int mid = (l+r) >> 1;
			ask.clear();
			for(int i = 0; i <= mid; i++)
				for(int j : s[i])
					ask.pb(j);	
			int x = query(ask);
			if(x == mx)
				r = mid;
			else
				l = mid+1;
		}
		
		vi ans(k, mx);
		ans[l] = query(complement(s[l], n));
		
		cout << '!';
		rep(i,0,k)
			cout << ' ' << ans[i];
		cout << endl;
		string fim;
		cin >> fim;
	}
}
