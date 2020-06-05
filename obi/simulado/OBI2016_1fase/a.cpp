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

string fine(string s) {
	string ret = "";
	allin(c, s) {
		if(c == '{' || c == '}') ret.pb(c);
	}
	return ret;
}

int main(){
	// FAST;
	int n;
	cin >> n;
	string str = "";
	cin.ignore();
	rep(i,0,n) {
		string atual; getline(cin, atual);
		str += fine(atual);
	}
	stack<int> s;
	bool bad = false;
	allin(c, str) {
		if(c == '{')
			s.push(1);
		else {
			if(s.empty()) bad = true;
			else s.pop();
		}
	}
	if(bad || s.size()) cout << "N\n";
	else cout << "S\n";
}
