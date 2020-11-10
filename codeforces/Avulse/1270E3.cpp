#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define x first
#define y second
#define pb push_back

int main() {
	int n; scanf("%d", &n);
	vector<pii> a(n);
	int fx, fy; scanf("%d %d", &fx, &fy);
	for(int i = 1; i < n; i++)
		scanf("%d %d", &a[i].x, &a[i].y), a[i].x -= fx, a[i].y -= fy;
	while(1) {
		bool ok[4]; memset(ok, 0, sizeof ok);
		for(int i = 0; i < n; i++) {
			for(int mask = 0; mask < 4; mask++)
				ok[mask] |= (((a[i].x&1)==(mask&1))&&((a[i].y&1)==((mask&2)>>1)));
		}
		int cnt = 0;
		for(int mask = 0; mask < 4; mask++)
			cnt += ok[mask];
		if(cnt > 1) {
			vector<int> ans;
			if(ok[1]||ok[2]) {
				for(int i = 0; i < n; i++)
					if((a[i].x&1)+(a[i].y&1) == 1)
						ans.pb(i+1);
			} else {
				for(int i = 0; i < n; i++)
					if((a[i].x&1)+(a[i].y&1) == 0)
						ans.pb(i+1);
			}
			printf("%d\n", (int)ans.size());
			for(int x : ans)
				printf("%d ", x);
			printf("\n");
			break;
		}
		for(pii& x : a)
			x.x >>= 1, x.y >>= 1;
	}
}