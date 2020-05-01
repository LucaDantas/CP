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

const int maxn = 1e5 + 100;

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
		set<int> dig;
		vi a(n);
		for(auto& it : a)
			cin >> it;
		for(auto it : a)
			dig.insert(it);
		if(k < (int)dig.size()){
			cout << -1 << '\n';
			continue;
		}
		for(int i = 1; i <= n && (int)dig.size() < k; i++)
			dig.insert(i);
		cout << n*dig.size() << endl;
		for(int i = 0; i < n; i++)
			for(auto now : dig)
				cout << now << ' ';
		cout << endl;
	}
}
