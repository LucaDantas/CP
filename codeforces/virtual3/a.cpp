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
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 110;
int c[maxn], p[maxn];

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		bool broke = false;
		for(int i = 1; i <= n; i++)
			cin >> p[i] >> c[i];
		for(int i = 1; i <= n; i++){
			if(c[i] > p[i] || p[i] < p[i-1] || c[i] < c[i-1] || (p[i] - p[i-1]) < (c[i] - c[i-1])){
				cout << "NO" << endl;
				broke = true;
				break;
			}
		}	
		if(!broke) cout << "YES" << endl;	
	}
}
