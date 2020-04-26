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

const int maxn = 4e5 + 100;
int pref[maxn];

ll solve(ll k, int n){
	return pref[n-1] * (k/n) + pref[k%n];
}

int main(){
	FAST;
	int t;
	cin >> t;
	while(t--){
		int a, b, q, p;
		cin >> a >> b >> q;
		p = a*b;
		if(a < b) swap(a, b);
		for(int i = 1; i < p; i++){
			pref[i] = pref[i-1];
			if(i % a % b != i % b % a)
				pref[i]++;
		}
		while(q--){
			ll l, r;
			cin >> l >> r;
			cout << solve(r, p) - solve(l-1, p) << endl;
		}
	}
}
