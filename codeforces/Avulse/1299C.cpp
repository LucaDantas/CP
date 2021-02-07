#include<cstdio>
#include<vector>
using namespace std;

#define pb push_back
#define sz(a) (int)a.size()

constexpr int maxn = 1e6+10;

long long p[maxn];

bool ccw(int a, int b, int c) {
	return (1ll*(b-a)*(p[c]-p[a])-1ll*(c-a)*(p[b]-p[a])) > 0;
}

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n+1);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	vector<int> hull = {0};
	for(int i = 1; i <= n; i++) {
		p[i] = p[i-1] + 1ll*a[i];
		while(sz(hull) >= 2 && !ccw(hull[sz(hull)-2], hull.back(), i))
			hull.pop_back();
		hull.pb(i);
	}
	int last = 0;
	for(int x : hull) {
		for(int i = last+1; i <= x; i++)
			printf("%.9lf ", (double)((long double)(p[x] - p[last])/(x-last)));
		last = x;
	}
	printf("\n");
}