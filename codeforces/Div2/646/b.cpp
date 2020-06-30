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
	int t; cin >> t;
	while(t--) {
		string s; cin >> s;
		if(sz(s) <= 2) {cout << "0\n"; continue;}
		int n = sz(s);
		vi pref0(n);
		vi pref1(n);
		vi suf0(n);
		vi suf1(n);
		pref0[0] = ((s[0]-'0')^1);
		pref1[0] = (s[0]-'0');
		suf0[n-1] = ((s[n-1]-'0')^1);
		suf1[n-1] = (s[n-1]-'0');
		rep(i,1,n) {
			pref0[i] = pref0[i-1] + ((s[i]-'0')^1);
			pref1[i] = pref1[i-1] + (s[i]-'0');
		}
		for(int i = n - 2; i >= 0; i--) {
			suf0[i] = suf0[i+1] + ((s[i]-'0')^1);
			suf1[i] = suf1[i+1] + (s[i]-'0');
		}
		int ans = min({pref0[n-1], pref1[n-1], suf1[0], suf1[0]});
		rep(i,0,n-1) {
			ans = min({ans, pref0[i] + suf1[i+1], pref1[i] + suf0[i+1]});
		}
		cout << ans << '\n';
	}
}
