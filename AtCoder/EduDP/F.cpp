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

const int maxn = 3e3 + 100;

char s[maxn], t[maxn];
int S = 0, T = 0;

int dp[maxn][maxn];

int solve(int a=0, int b=0){
	if(a >= S || b >= T) return dp[a][b] = 0;
	
	if(dp[a][b] != -1) return dp[a][b];
	
	if(s[a] == t[b])		
		return dp[a][b] = 1 + solve(a+1, b+1);
	
	if(solve(a+1, b) > solve(a, b+1))
		return dp[a][b] = solve(a+1,b);
	
	else
		return dp[a][b] = solve(a, b+1);
}

string find(int a=0, int b=0){
	if(a >= S || b >= T) return "";
	
	if(s[a] == t[b]){
		return s[a] + find(a+1, b+1);
	}
	
	if(dp[a+1][b] > dp[a][b+1])
		return find(a+1, b);
	else
		return find(a, b+1);
}

int main(){
	FAST;
	cin >> s >> t;
	trav(it, s){
		if(it - 'a' < 0 || it - 'z' > 0) break;
		S++;
	}
	
	trav(it, t){
		if(it - 'a' < 0 || it - 'z' > 0) break;
		T++;
	}
	
	clr(dp, -1);
	solve();
	
	if(dp[0][0] == 0) puts("");
	else cout << find() << '\n';
}
