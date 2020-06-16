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

const int maxn = 1e4 + 100;

int dp[maxn][maxn]; // dp[i][k] = maior valor do pref até i colando k etiquetas
int a[maxn];

int main(){
	int n, K, C;
	scanf("%d %d %d", &n, &K, &C);
	
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= K; j++)
			dp[i][j] = -0x3f3f3f3f;

	dp[0][0] = 0; // Não colar nada, caso base

	for(int i = 1; i <= n; i++) {
		dp[i][0] = dp[i-1][0] + a[i];
		for(int k = 1; k <= min(i/C, K); k++) { // Só podemos ter no máximo i/c etiquetas em cada nível
			dp[i][k] = max(dp[i-C][k-1], dp[i-1][k] + a[i]);
		}
	}

	printf("%d\n", dp[n][K]);
}
