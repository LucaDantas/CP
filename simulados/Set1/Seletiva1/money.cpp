#include<cstdio>
#include<utility>
#include<algorithm>
#include<vector>
using namespace std;

constexpr int maxn = 5e5+10;

#define ff first
#define ss second

using pii = pair<int,int>;

pii pts[2][maxn];

long long ans = 0;

long long get(pii a, pii b) {
	if(b.ff < a.ff || b.ss < a.ss) return -1;
	return 1ll*(b.ff-a.ff)*(b.ss-a.ss);
}

// tem q se ligar pra n colocar cara q n tem nenhum par bom
// pq senao da errado quando eu for olhar ele como m
void solve(int l, int r, int l2, int r2) {
	if(l > r) return;
	int m = (l+r) >> 1;
	pair<long long,int> best = {-1, l2};
	for(int i = l2; i <= r2; i++)
		best = max(best, {get(pts[0][m], pts[1][i]), i});
	ans = max(ans, best.ff);
	solve(l, m-1, l2, best.ss);
	solve(m+1, r, best.ss, r2);
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		scanf("%d %d", &pts[0][i].ff, &pts[0][i].ss);
	sort(pts[0], pts[0]+n);

	for(int i = 0; i < m; i++)
		scanf("%d %d", &pts[1][i].ff, &pts[1][i].ss);
	sort(pts[1], pts[1]+m);
	
	vector<pii> escadinha;
	for(int i = 0; i < m; i++) {
		while(escadinha.size() && escadinha.back().ss <= pts[1][i].ss)
			escadinha.pop_back();
		escadinha.push_back(pts[1][i]);
	}
	for(int i = 0; i < m; i++)
		pts[1][i] = {0, 0};
	m = (int)escadinha.size();
	for(int i = 0; i < m; i++)
		pts[1][i] = escadinha[i];
	escadinha.clear();
	
	for(int i = 0; i < n; i++)
		if((!escadinha.size() || escadinha.back().ss > pts[0][i].ss) &&
			(*lower_bound(pts[1], pts[1]+m, pts[0][i])).ss > pts[0][i].ss)
			escadinha.push_back(pts[0][i]);
	for(int i = 0; i < n; i++)
		pts[0][i] = {0, 0};
	n = (int)escadinha.size();
	for(int i = 0; i < n; i++)
		pts[0][i] = escadinha[i];

	solve(0, n-1, 0, m-1);
	printf("%lld\n", ans);
}