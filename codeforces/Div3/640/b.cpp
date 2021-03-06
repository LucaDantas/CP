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

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
		//check odd
		if((n-k+1)&1 && (n-k+1) > 0){
			cout << "YES\n";
			cout << n-k+1;
			while(--k) cout << " 1"; 
			cout << '\n';
			continue;
		}
		//check even
		if(!((n-(k-1)*2)&1) && (n-(k-1)*2) > 0){
			cout << "YES\n";
			cout << n-(k-1)*2;
			while(--k) cout << " 2"; 
			cout << '\n';
			continue;
		}
		cout << "NO\n";
	}
}
