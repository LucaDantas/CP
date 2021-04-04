#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 210, maxm = 1e4+10;

int n, m;

struct DSU
{
	int pai[maxn], peso[maxn];
	bool get_ans = 0;
	void init() { for(int i = 0; i <= n; i++) pai[i] = i, peso[i] = 1; }
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	bool join(int a, int b) {
		int x = a, y = b;
		a = find(a), b = find(b);
		if(a == b) return 0;
		if(peso[a] < peso[b])
			swap(a, b);
		pai[b] = a;
		peso[a] += peso[b];
		if(get_ans) printf("%d %d\n", x, y);
		return 1;
	}
} dsu;


struct Edge
{
	int a, b, t, c;
} edges[maxm];

long long val(Edge x, int A, int B) { 
	return 1ll * x.t * A + 1ll * x.c * B;
}

pair<int,int> get(int A, int B) {
	dsu.init();
	pair<int,int> ans = {0, 0};
	sort(edges, edges+m, [A, B](Edge x, Edge y) {
		if(val(x, A, B) == val(y, A, B)) return x.t < y.t;
		return val(x, A, B) < val(y, A, B);
	});
	for(int i = 0; i < m; i++)
		if(dsu.join(edges[i].a, edges[i].b))
			ans.first += edges[i].t, ans.second += edges[i].c;
	return ans;
}

struct ANS {
	long long v; int t, c, A, B;
	ANS() : v() {}
	ANS(int T, int C, int a, int b) {
		v = 1ll*T*C, t = T, c = C, A = a, B = b;
	}
} ans;

ANS min(ANS a, ANS b) {
	if(a.v < b.v) return a;
	return b;
}

using pii = pair<int,int>;
bool cross(pii a, pii b, pii c) {
	b.first -= a.first;
	c.first -= a.first;
	b.second -= a.second;
	c.second -= a.second;
	return (1ll * b.first * c.second - 1ll * b.second * c.first) != 0ll;
}

void solve(pii l, pii r) {
	// we want to find the vector parallel to the line between l and r
	// because the point that minimizes the dot with such vector is
	// the 'furthest point' in the direction of that line

	// we can find such vector by taking the slope of the line and
	// using the standard formula to calculate the slope of the parelell
	// line.


	int x = r.first - l.first, y = r.second - l.second;
	pii m = get(-y, x); // keep things positive for simplicity
	
	ans = min(ans, ANS(m.first, m.second, -y, x));
	if(cross(l, m, r)) {
		solve(l, m);
		solve(m, r);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, t, c; scanf("%d %d %d %d", &a, &b, &t, &c);
		edges[i] = {a, b, t, c};
	}
	pair<int,int> l = get(1, 0);
	pair<int,int> r = get(0, 1);
	ans = min(ANS(l.first, l.second, 1, 0), ANS(r.first, r.second, 0, 1));
	solve(l, r);
	dsu.get_ans = 1;
	printf("%d %d\n", ans.t, ans.c);
	get(ans.A, ans.B);
}