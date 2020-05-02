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

const int maxn = 1e6 + 100;
bitset<maxn> bt;

int main(){
	FAST;
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		if(s.size() > 7) continue;
		if(stoi(s) < 0) continue;
		if(stoi(s) >= maxn) continue;
		bt.set(stoi(s));
	}
	for(int i = 0; i < maxn; i++){
		if(bt.test(i)) continue;
		cout << i << endl;
		return 0;
	}
	assert(0);
}
