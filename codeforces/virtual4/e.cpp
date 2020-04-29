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
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const ll MOD = 998244353;

ll mulmod(ll a, ll b, ll c){ // multiplicacao modular
    // multiplicar (a*b) equivale a sum(a * 2^i * b_i), onde (a*2^i) é representado
    // na linha do meio, b_i na primeira linha, e o passo de sum na ultima linha
    ll ans = 0;
    a %= c;
    while(b > 0){
        if(b%2) ans = (ans + a) % c;
        a = (a * 2) % c;
        b >>= 1;
    }
    return ans % c;
}

ll power(ll a, ll b, ll p){ // recursivo
	if(b == 0) return 1;
	if(b == 1) return a;
	ll x = mulmod(a, a, p);
	if(b&1) return mulmod(power(x, b/2, p), a, p);
	return power(x, b/2, p)%p;
}

ll inverso( ll a, ll pmod ){
    // a^(m-1) ≡ 1 (mod m), m primo
    // a^(-1) ≡ a^(m-2) (mod m)
    // o inverso de a eh a^(m-2)
    return power( a, pmod - 2 , pmod);
}

int main(){
	FAST;
	ll n, m, L, R;
	cin >> n >> m >> L >> R;
	if((n*m) % 2){
		cout << power(R-L+1, n*m, MOD) << endl; 
	}
	else{
		int k = R-L+1;
		ll E = (k/2), O = k-E;
		ll ans = (power(E+O, n*m, MOD) + power((E-O+MOD)%MOD, n*m, MOD)) % MOD;
		cout << mulmod(ans, inverso(2, MOD), MOD) << endl;
	}
}
