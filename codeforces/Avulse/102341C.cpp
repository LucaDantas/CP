#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

#define ff first
#define ss second

constexpr int maxn = 2010;

int dp[maxn][maxn], n;

int query(int a, int b) {
	if(a <= 0 || a > n || b <= 0 || b > n) return 0;
	if(dp[a][b]) return dp[a][b];
	printf("? %d %d\n", a, b); fflush(stdout);
	int& v = dp[a][b]; scanf("%d", &v);
	return v;
}

struct Item {
	int val, x, y;
	Item(int a1 = 0, int b1 = 0, int c1 = 0) : val(a1), x(b1), y(c1) {}
	bool operator<(Item it) const {
		std::pair<int,std::pair<int,int>> p = {val, {x, y}}, p2 = {it.val, {it.x, it.y}};
		return p < p2;
	}
	bool operator>(Item it) const {
		std::pair<int,std::pair<int,int>> p = {val, {x, y}}, p2 = {it.val, {it.x, it.y}};
		return p > p2;
	}
	bool operator==(Item it) const {
		std::pair<int,std::pair<int,int>> p = {val, {x, y}}, p2 = {it.val, {it.x, it.y}};
		return p == p2;
	}
	bool operator>=(Item it) const {
		std::pair<int,std::pair<int,int>> p = {val, {x, y}}, p2 = {it.val, {it.x, it.y}};
		return p >= p2;
	}
};

void ans(Item mx) { printf("! %d %d\n", mx.x, mx.y); exit(0); }
Item get(int i, int j) { Item a(query(i, j), i, j); return a; }

Item redor(Item it) {
	int x = it.x, y = it.y;
	for(int i = x-1; i <= x+1; i++)
		for(int j = y-1; j <= y+1; j++)
			it = std::max(it, get(i, j));
	return it;
}

void solve(int a, int x, int b, int y, Item mx) {
	{
		Item opa; int m = (b+y) >> 1;
		for(int i = a; i <= x; i++)
			opa = std::max(opa, get(i, m));
		mx = std::max(mx, redor(opa));
		if(mx.y <= m) y = m-1;
		else b = m+1;
		if(mx >= redor(mx)) ans(mx);
	}
	{
		Item opa; int m = (a+x) >> 1;
		for(int i = b; i <= y; i++)
			opa = std::max(opa, get(m, i));
		mx = std::max(mx, redor(opa));
		if(mx.x <= m) x = m-1;
		else a = m+1;
		if(mx >= redor(mx)) ans(mx);
	}
	solve(a, x, b, y, mx);
}

int main() {
	scanf("%d", &n);
	Item sla;
	solve(1, n, 1, n, sla);
}
