#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<ll>> matrix;

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

const int MOD = 1e9 + 7;

matrix operator *(matrix a, matrix b){
	int n = (int)a.size(); //# rows of a
	int m = (int)b.size(); //# items in each row of a / column of b
	int p = (int)b[0].size(); //# columns of b
	matrix c(n, vector<ll>(p));
	vector<ll> col(m);
	for(int j = 0; j < p; j++){ //for every column of b
		for(int k = 0; k < m; k++) 
			col[k] = b[k][j];
		for(int i = 0; i < n; i++){ //multiply by every row in a
			ll sum = 0;
			for(int k = 0; k < m; k++) //for every item in row i of a, multiply by every item in column j of b
				sum = ((sum + (a[i][k]*col[k])%MOD)%MOD + MOD)%MOD; //maybe too careful
				//sum = (sum + (a[i][k]*col[k])%MOD)%MOD;
			c[i][j] = sum;
		}
	}
	return c;
}

matrix identity(int siz){
	matrix ret(siz, vector<ll>(siz));
	for(int i = 0; i < siz; i++)
		ret[i][i] = 1;
	return ret;
}

matrix pow(matrix A, ll p){
	matrix ret = identity((int)A.size());
	while(p > 0){
		if(p&1)
			ret = ret*A;
		A = A*A;
		p >>= 1;
	}
	return ret;
}

int main(){
	FAST;
	int n; cin >> n;
	matrix a = {{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}};
	cout << (pow(a, n))[0][0] << endl;
}
