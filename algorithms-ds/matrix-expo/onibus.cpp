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
#define _ << " " <<

const int maxn = 1e5 + 100;
const int MOD = 1e6;

//Solve recurrence for f(n) = K*f(n-1) + L*f(n-2)

matrix operator*(matrix a, matrix b){
	int n = sz(a);
	int m = sz(b[0]);
	matrix c(n, vector<ll>(m));
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for(int k = 0; k < n; k++)
				c[i][j] = (c[i][j] + (a[i][k]*b[k][j])%MOD)%MOD;
	return c;
}

matrix identity(ll siz){
	matrix ret(siz,vector<ll>(siz));
	for(int i = 0; i < siz; i++)
		ret[i][i] = 1;
	return ret;
}

matrix pow(matrix A, ll p){
	matrix ret = identity(sz(A));
	while(p > 0){
		if(p&1)
			ret = ret*A;
		A = A*A;
		p >>= 1;
	}
	return ret;
}

string norm(ll a){
	string p = to_string(a);
	reverse(all(p));
	while(p.size() < 6)
		p.pb('0');
	reverse(all(p));
	return p;
}

int main(){
	FAST;
	ll N, K, L;
	while(cin >> N >> K >> L){
		K %= MOD;
		L %= MOD;
		N /= 5;
		if(N==1) cout << norm(K) << endl;
		else if(N==2) cout << norm((K*K%MOD + L)%MOD) << endl;
		else{
    		matrix a = {{(K*K%MOD + L)%MOD}, {K%MOD}};
    		matrix b = {{K, L},{1,0}};
    		cout << norm((pow(b, N-2)*a)[0][0]) << '\n';
		}
	}
}
