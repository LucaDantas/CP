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

//int a[maxn];

vi a;

int n, k;

int main(){
	FAST;
	int t; cin >> t;
	while(t--){
		cin >> n >> k;
		a = vi(n);
		vi pos;
		rep(i,0,n){
			cin >> a[i];
			if(a[i] == k) pos.pb(i);
		}
		bool broke = false;
		if(pos.empty()) {cout << "no\n"; continue;}
		if(n==1) {cout << "yes\n"; continue;}
		for(int i = 1; i < n; i++)
			if(a[i] >= k && a[i-1] >= k) {cout << "yes\n"; broke = true; break;}
		if(!broke) cout << "no\n";
	}
}
