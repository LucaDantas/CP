#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

#define x first
#define y second

inline ll sq(int x) { return 1ll*x*x; }
ll dist(pii a, pii b) { return sq(a.x-b.x) + sq(a.y-b.y); }

int main() {
	int n; scanf("%d", &n);
	vector<pii> a(n);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &a[i].x, &a[i].y);
	ll g = dist(a[0], a[1]);
	for(int i = 2; i < n; i++)
		g = __gcd(g, dist(a[0], a[i]));
	int cnt = 0;
	for(int i = 1; i < n; i++)
		if(dist(a[0], a[i]) / g % 2 == 0)
			cnt++;
	printf("%d\n", cnt+1);
	for(int i = 0; i < n; i++)
		if(dist(a[0], a[i]) / g % 2 == 0)
			printf("%d ", i+1);
	printf("\n");
}