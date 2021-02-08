#include<cstdio>
#include<cmath>
#include<utility>
using namespace std;

using pii = pair<int,int>;

#define ff first
#define ss second

constexpr int maxn = 310;

pii pt[maxn];

double sq(int a) {return (double)(1ll*a*a);}
double dist2(pii a, pii b) {return sqrt(sq(a.ff-b.ff) + sq(a.ss-b.ss));}
double dist(int a, int b) {return dist2(pt[a], pt[b]);}

double dp[maxn][maxn][2];

bool tem[maxn][maxn];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d %d", &pt[i].ff, &pt[i].ss);
		
		int m; scanf("%d", &m);
		for(int i = 0, a, b; i < m; i++)
			scanf("%d %d", &a, &b), tem[a-1][b-1] = tem[b-1][a-1] = 1;
		
		for(int tam = 1; tam < n; tam++) {
			for(int l = 0; l < n; l++) {
				for(int dir : {0, 1}) {
					int val_dir = dir?1:-1;
					int r = (l + tam*val_dir + n)%n;
					double& aq = dp[l][r][dir];
					for(int x = (l+val_dir+n)%n; x != (r+val_dir+n)%n; x = (x+val_dir+n)%n) {
						if(tem[l][x]) {
							aq = max(aq, dp[x][r][dir] + dist(l, x));
							aq = max(aq, dp[x][(l+val_dir+n)%n][!dir] + dist(l, x));
						}
					}
				}
			}
		}

		double ans = 0;
		for(int i = 0; i < n; i++)
			ans = max(ans, dp[i][(i+n-1)%n][1]);
		printf("%.6lf\n", ans);

		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dp[i][j][0] = dp[i][j][1] = tem[i][j] = 0;
	}
}