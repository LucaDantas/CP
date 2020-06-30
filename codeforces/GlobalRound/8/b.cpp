#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define sz(a) ((int)(a).size())
#define rep(i,a,b) for(int i=(a); i<(b); i++)
#define trav(it, a) for(auto& it : a)
#define allin(it, a) for(auto it : a)
#define read(v, a, b) for(int i=(a); i<(b); i++) scanf("%d", &v[i]);
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define db(x) cerr << #x << " == " << x << endl

const int maxn = 1e5 + 100;

const char str[] = {'c','o','d','e','f','o','r','c','e','s'};

// ll power(int b) {
// 	ll ans = 1;
// 	rep(i,0,10)
// 		ans *= b;
// 	return ans;
// }

// int menor_pot(ll k) {
// 	ll ans = 1;
// 	while(power(ans) < k) {
// 		ans++;
// 	}
// 	return (int)ans-1;
// }

// int outra(int k, int p) {
// 	int ans = 0;
// 	ll val = power(p);
// 	while(val < k) {
// 		ans++;
// 		val /= p;
// 		val *= p+1;
// 	}
// 	return ans;
// }

int main(){
	ll k; cin >> k;
	vi a(10,1);
	ll product = 1;
	int pos = 0;
	while(product < k) {
		product /= a[pos];
		product *= a[pos]+1;
		a[pos]++;
		pos++;
		pos%=10;
	}
	rep(i,0,10) rep(kk,0,a[i]) cout << str[i];
	cout << "\n";
}
