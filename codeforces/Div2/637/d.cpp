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
#define printvec(v) for(int i=0; i < sz(v); i++) cout << v[i] << ' '
#define clr(a,v) memset(a, v, sizeof(a))
#define all(a) (a).begin(),(a).end()
#define FAST cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)
#define max3(x, y, z) max(x, max(y, z))
#define db(x) cerr << #x << " == " << x << endl
#define _ << " " <<

const int maxn = 2000 + 100;

vector<string> digits = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

int main(){
	FAST;
	int n, k;
	cin >> n >> k;
	vector<vector<int>> dist(n, vector<int>(10));
	vector<string> s(n);
	for(int i = 0; i < n; i++){
		cin >> s[i];
		for(int d = 0; d < 10; d++){
			for(int j = 0; j < 7; j++){
				char x = s[i][j];
				char y = digits[d][j];
				if(x == '1' && y == '0'){
					dist[i][d] = -1;
					break;
				}
				if(x == '0' && y == '1'){
					dist[i][d]++;
				}
			}
		}
	}
	vector<vi> dp(n+1, vi(k+1));
	dp[n][0] = 1;
	for(int i = n; i > 0; i--){
		for(int j = 0; j <= k; j++){
			if(dp[i][j]){
				for(int d = 0; d < 10; d++){
					if(dist[i-1][d] != -1 && j + dist[i-1][d] <= k){
						dp[i-1][j + dist[i-1][d]] = 1;
					}
				}
			}
		}
	}
	if(dp[0][k] == 0){ cout << -1 << endl; return 0;}
	for(int i = 0; i < n; i++){
		for(int d = 9; d >= 0; d--){
			if(dist[i][d] != -1 && k >= dist[i][d] && dp[i+1][k-dist[i][d]]){
				cout << d;
				k -= dist[i][d];
				break;
			}
		}
	}
	cout << endl;
	return 0;
}
