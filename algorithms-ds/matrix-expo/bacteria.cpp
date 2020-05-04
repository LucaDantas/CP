#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<ll>> matrix;

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

const int MOD = 13371337;

matrix operator*(matrix a, matrix b){
	int rows = sz(a);
	int columns = sz(b[0]);
	matrix c(rows, vector<ll>(columns));
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++){
			ll s = 0;
			for(int k = 0; k < rows; k++)
				s = (((s%MOD + ((a[i][k]%MOD)*(b[k][j]%MOD)%MOD))%MOD))%MOD;
			c[i][j] = s;
		}
	return c;
}

matrix identity(int siz){
	matrix ret(siz, vector<ll>(siz));
	for(int i = 0; i < siz; i++)
		ret[i][i] = 1;
	return ret;		
}

matrix power(matrix A, ll e){
	matrix ret = identity(sz(A));
	while(e > 0){
		if(e&1) ret = ret*A;
		A = A*A;
		e >>= 1;
	}
	return ret;
}

int main(){
	FAST;
	//solve recurrence of g(n) = g(n-1) + g(n-2) + g(n-3) + g(n-4)
	//The answer f(n) = g(n) + g(n-1) + g(n-2) + g(n-3)
	while(true){
		ll n; cin >> n;
		if(!n) break;
		ll a1, a2, a3, a4; cin >> a1 >> a2 >> a3 >> a4;
		matrix top = {{1, 1, 1, 1}, {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}};
		matrix base = {{a4},{a3},{a2},{a1}};
		matrix ans = power(top, n-4)*base;
		cout << ((ans[0][0] +	ans[1][0])%MOD + (ans[2][0] + ans[3][0])%MOD)%MOD << endl;
	}
}
