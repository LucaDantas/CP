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

bool open(char c){
	if( c=='{' || c== '[' || c == '(') return true;
	return false; 
}

char inv(char c){
	if( c=='}') return '{';
	if(c== ']') return '[';
	return '(';
}

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		bool ok = true;
		string a; cin >> a;
		stack<char> s;
		for(auto c : a){
			if(open(c)) s.push(c);
			else{
				if(!s.empty() && s.top() == inv(c)) s.pop();
				else {ok = false; break;}
			}
		}
		if(ok && s.empty()) cout << "S\n";
		else cout << "N\n";
	}
}
