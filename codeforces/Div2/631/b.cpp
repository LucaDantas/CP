#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair
#define endl '\n'
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2e5 + 100;

bool check(const vi &v, int pos){
	set<int> s;
	for(int i = 0; i < pos; i++){
		if(v[i] > pos) return false;
		s.insert(v[i]);
	}
	if(sz(s) != pos) return false;
	s.clear();
	for(int i = pos; i < sz(v); i++){
		if(v[i] > sz(v)-pos) return false;
		s.insert(v[i]);
	}
	if(sz(s) != sz(v) - pos) return false;
	return true; 
}

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		vi a(n);
		read(a, 0, n);
		int maior = *max_element(all(a));
		bool a1 = check(a, maior);
		bool a2 = maior * 2 != n && check(a, n-maior);
		cout << a1 + a2 << endl;
		if(a1) cout << maior _ n-maior << endl;
		if(a2) cout << n-maior _ maior << endl;
	}
}
