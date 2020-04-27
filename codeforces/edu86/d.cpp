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
#define dec(i,n,a) for(int i=(n); i>=(a); i--)
#define read(v, a, b) for(int i=(a); i<(b); i++) cin>>v[i]
#define printv(v, a, b) for(int i=(a); i < (b); i++) cout << v[i] << ' '
#define printvec(v) for(int i=0; i < sz(v); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

vi c;
vector<vi> connard;
multiset<int, greater<int>> s;

int main(){
	FAST;
	int n, k;
	cin >> n >> k;
	c.resize(k);
	for(int i = 0, a; i < n; i++){
		cin >> a;
		s.insert(a);
	}
	for(int i = 0; i < k; i++){
		cin >> c[i];
	}
	reverse(all(c));
	while(s.size()){
		int offset=0;
		vi putain;
		auto itr_baixo = upper_bound(all(c), offset);
		while(itr_baixo != c.end()){
			int x = c.end()-itr_baixo;
			auto it_cima = s.lower_bound(x);
			if(it_cima == s.end()) break;
			putain.pb(*it_cima);
			s.erase(it_cima);
			itr_baixo = upper_bound(all(c), ++offset);
		}
		connard.pb(putain);		
	}
	cout << connard.size() << endl;
	for(auto top : connard){
		cout << top.size() << ' ';
		for(auto it : top)
			cout << it << ' ';
		cout << endl;
	}
}
