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

const int maxn = 1e3 + 100;

int ans[maxn][maxn];

void build(int n, int ind, int cor){
	if(n==0) return;
	for(int i = ind; i < n; i++){
		ans[i][ind] = cor;
		ans[i][n-1] = cor;
		ans[ind][i]=cor;
		ans[n-1][i]=cor;
	}
	build(n-2,ind+2, 1);
}

int main(){
	//FAST;
	int n; scanf("%d", &n);
	if(n%4 != 2) {puts("-1"); return 0;}
	build(n,0,1);
	rep(i, 0, n) rep(j, 0, n) printf("%d%c", ans[i][j], " \n"[j==n-1]);
}
