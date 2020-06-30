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

bool check_num(string s) {
	if(sz(s) == 0) return false;
	// db(s);
	if(s[0] == '0' && sz(s) > 1) return false;
	allin(c, s) {
		if(c < '0' || c > '9') return false;
	}
	return true;
}

int main(){
	string s; cin >> s;
	// string a = "", b = "";
	vector<string> a, b;
	string now = "";
	allin(c,s) {
		if(c == ',' || c == ';') {
			if(check_num(now)) a.pb(now); 
			else b.pb(now);
			now = "";
		}
		else {
			now.pb(c);
		}
	}
	if(check_num(now)) a.pb(now); 
	else b.pb(now);
	if(sz(a)) {
		cout << "\"";
		rep(i,0,sz(a)) {cout << a[i]; if(i < sz(a)-1) cout << ',';}
		cout << "\"\n";
	}
	else cout << "-\n";
	if(sz(b)) {
		cout << "\"";
		rep(i,0,sz(b)) {cout << b[i]; if(i < sz(b)-1) cout << ',';}
		cout << "\"\n";
	}
	else cout << "-\n";
}
