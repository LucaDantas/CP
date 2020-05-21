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

const int maxn = 450;

int n, a[maxn], sum[maxn], dp[maxn][maxn];

// I still have to find out what to do when we have situations of the kind
// X Y X and we want to combine those three and the problem is that we need
// to merge them and Y can be an interval of arbritary size so the naive way 
// to do the transition to separare in three intervals is O(n²) in the transition
// which makes the overral too slow O(n⁴) gotto solve this tomorrow

// UPD:
// My idea is to do a two pointers on the transition and we need to exploit the fact that
// we can only combine the left-right two intervals if they have the same size, and to be
// able to use a two pointers approach we also need to notice that the values are always 
// greater than zero, which means that we can go adding on the smallest value pointer
// (one starts at the left and walks towards the right and the other one is the opposite) 
// and when the two values are the same we can simply check if two three intervals formed
// between those pointers can be merged, if they can we end, otherwise we increment both 
// pointers, and if we don't find anything and l > r we end the process

int interval(int x, int y){
	return sum[y] - sum[x-1];
}

int solve(int l, int r){
	if(l >= r) return 1;
	if(dp[l][r] != -1) return dp[l][r];
	
	int ptrL = l, ptrR = r;
	
	while(ptrL < ptrR){
		if(interval(l, ptrL) == interval(ptrR, r)){
			if(solve(l, ptrL) && solve(ptrL+1, ptrR-1) && solve(ptrR, r))
				return dp[l][r] = 1;
			else
				ptrL++, ptrR--;
		}
		
		else if(interval(l, ptrL) < interval(ptrR, r))
			ptrL++;
		else
			ptrR--;
	}
	
	return dp[l][r] = 0;
}

int main(){
	scanf("%d", &n);
	
	rep(i,1,n+1){
		scanf("%d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}

	clr(dp, -1);
		
	rep(i,1,n+1)
		dp[i][i] = 1;
	
	rep(i,1,n+1)
		rep(j,i,n+1)
			solve(i,j);

	int ans = -1;
	
	rep(i,1,n+1)
		rep(j,i,n+1)
			if(dp[i][j] == 1)
				ans = max(ans, interval(i, j));
				
	printf("%d\n", ans);
}
