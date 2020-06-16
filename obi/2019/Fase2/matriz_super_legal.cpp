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

int n, m, ans = -1;

int grid[maxn][maxn], solve[maxn][maxn];

int main(){
	scanf("%d %d", &n ,&m);
	
	rep(i,0,n)
		rep(j,0,m)
			scanf("%d", &grid[i][j]);
			
	rep(i,1,n)
		rep(j,1,m)
			solve[i-1][j-1] = (grid[i][j] + grid[i-1][j-1] <= grid[i][j-1] + grid[i-1][j]);

	vi arr(m-1);
	rep(i,0,n-1){
		
		rep(j,0,m-1){
			if(solve[i][j])
				arr[j]++;
			else
				arr[j] = 0;
		}
		
		stack<int> s; //stack only contains the index of the top item
		rep(j,0,m-1){
			while(!s.empty() && arr[s.top()] >= arr[j]){
				int id = s.top();
				int alt = arr[id];
				s.pop();
				int left = s.empty()? 0 : s.top()+1;
				ans = max(ans, (alt + 1)*(j - left + 1)); 
			}
			s.push(j);
		}
		
		while(!s.empty()){
			int id = s.top();
			int alt = arr[id];
			s.pop();
			int left = s.empty()? 0 : s.top()+1;
			ans = max(ans, (alt + 1)*( (m - 1) - left + 1)); 
		}
	}
	
	printf("%d\n", ans);
}
