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

int min_dig(ll a){
	string s = to_string(a);
	int ans = 50;
	for(auto c : s)
		ans = min(ans, c-'0');
	return ans;
}

int max_dig(ll a){
	string s = to_string(a);
	int ans = 1;
	for(auto c : s)
		ans = max(ans, c-'0');
	return ans;
}

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		ll a, k;
		cin >> a >> k;
		k--;
		int top = min_dig(a);
		while(k && top != 0){
			a += top * max_dig(a);
			top = min_dig(a);
			k--;
			//db(a);
		}
		cout << a << '\n';
	}
}
