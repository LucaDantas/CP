#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

long long dist[maxn];

int main() {
	long long h; scanf("%lld", &h); --h;
	int a[3]; for(int i = 0; i < 3; i++) scanf("%d", &a[i]);
	
	priority_queue<pair<long long,int>, vector<pair<long long, int>>, greater<pair<long long,int>>> q;
	
	memset(dist, 0x3f, sizeof dist);
	q.push({0, 0}); dist[0] = 0;
	
	while(q.size()) {
		int u = q.top().second; q.pop();
		if(dist[(u + a[0]) % a[2]] > dist[u] + a[0])
			dist[(u + a[0]) % a[2]] = dist[u] + a[0], q.push({dist[(u + a[0]) % a[2]], (u + a[0]) % a[2]});
		if(dist[(u + a[1]) % a[2]] > dist[u] + a[1])
			dist[(u + a[1]) % a[2]] = dist[u] + a[1], q.push({dist[(u + a[1]) % a[2]], (u + a[1]) % a[2]});
	}
	long long ans = 0;
	for(int i = 0; i < a[2]; i++)
		if(h >= dist[i]) ans += (h-dist[i]) / a[2] + 1;
	printf("%lld\n", ans);
}
