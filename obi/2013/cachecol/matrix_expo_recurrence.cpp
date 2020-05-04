#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;

#define endl '\n'
#define sz(a) ((int)(a).size())
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<
const ll MOD = 1e9 + 7;

//Solve for the n-th item item of the recurrence
//f(i) = 5f(i-1) - 2f(i-2)

//vector[i][0] represents the first item of the row
//vector[0][i] represents the top item of the column

matrix operator *(matrix a, matrix b) {
	int n = (int)a.size();
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c(n, vector<ll>(p));
	vector<ll> col(m);
	for (int j = 0; j < p; j++) {
		for (int k = 0; k < m; k++)
			col[k] = b[k][j]%MOD;
		for (int i = 0; i < n; i++) {
			ll s = 0;
			for (int k = 0; k < m; k++)
				s = ((s%MOD+((a[i][k]%MOD) * (col[k]%MOD))%MOD)%MOD + MOD)%MOD;
			c[i][j] = s;
		}
	}
	return c;
}

matrix identity(int siz){
	matrix ret(siz, vector<ll>(siz));
	for(int i = 0; i < siz; i++)
		for(int j = 0; j < siz; j++)
			if(i==j)
				ret[i][j] = 1;
	return ret;
}

matrix power(matrix A, ll p){
	matrix ret = identity(sz(A));
	while(p > 0){
		if(p&1) ret = ret*A;
		A = A*A;
		p>>=1;
	}
	return ret;
}


int main(){
	ll n; cin >> n;
	if(n==1) {cout << 12 << endl; return 0;}
	if(n==2) {cout << 54 << endl; return 0;}
	matrix base = {{54}, {12}};
	matrix top = {{5, -2},{1, 0}};
	matrix ans = power(top, n-2)*base;
	cout << ans[0][0] << endl;
}
