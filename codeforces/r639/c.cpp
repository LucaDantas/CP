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

const int maxn = 2e5 + 100;
bool tenso[maxn];

int mod(int a, int p){
	int r = a%p; 
	if(r < 0) r += p;
	return r;
} 


int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		bool broke = false;
		int n; cin >> n;
		for(int i = 0; i < n; i++){
			int v; cin >> v;
			int pos = mod(v,n);
			pos = (i+pos)%n;
			if(tenso[pos] && !broke){
				cout << "NO\n";
				broke = true;
			}
			tenso[pos] = 1;
		}
		if(!broke) cout << "YES\n";
		for(int i = 0; i <= n; i++)
			tenso[i] = 0;
	}
}
