#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;
typedef pair<ll, pair<ll,ll>> trio;

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

matrix power(matrix A, ll p){
	if(p==1)
		return A;
	if(p%2)
		return (A * (power(A, p-1)));
	matrix X = power(A, (p>>1));
	return X*X;
}

bool operator !=(trio a, trio b){
	if(a.first != b.first && a.second.first != b.second.first && a.second.second != b.second.second)
		return true;
	return false;
}

matrix adjmat(12, vector<ll>(12));

int main(){
	ll n; cin >> n;
	if(n==1) {cout << 12 << endl; return 0;}
	if(n==2) {cout << 54 << endl; return 0;}
	trio possible[12] = {{1,{2,1}}, {1,{3,1}}, {2,{1,2}}, {3,{1,3}}, {3,{2,3}}, {2,{3,2}},{1,{2,3}}, {1,{3,2}}, {2,{1,3}}, {2,{3,1}}, {3,{1,2}}, {3,{2,1}}};
	for(int i = 0; i < 12; i++)
		for(int j = 0; j < 12; j++)
			if(possible[i] != possible[j])
				adjmat[i][j] = 1;
	matrix ans = power(adjmat, n-1);
	ll sum = 0;
	for(int i = 0; i < 12; i++)
		for(int j = 0; j < 12; j++)
			sum = (sum+ans[i][j])%MOD;
	cout << sum << endl;
}

