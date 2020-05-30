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

const int maxn = 110;

bool grid[maxn][maxn]; //filled with 0's

int main(){
	int n;
	scanf("%d", &n);
	int ans = 0;
	for (int k = 0; k < n; k++) {
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		for (int i = x1; i < x2; i++) {
			for (int j = y1; j < y2; j++) {
				grid[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			ans += grid[i][j];
		}
	}
	printf("%d\n", ans);
}
