#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 0x3f3f3f3f;

int check(int a, int b, int x, int y) {
	// a -> x, b -> y
	if(x < a || y < b)
		return inf;
	return (x-a)*y + (y-b)*x - (x-a)*(y-b);
}

int main() {
	int a, l, n; scanf("%d %d %d", &a, &l, &n);
	int ans = inf, id = -1;
	for(int i = 0; i < n; i++) {
		int x, y; scanf("%d %d", &x, &y);
		if(check(a, l, x, y) < ans)
			ans = check(a, l, x, y), id = i+1;
		if(check(a, l, y, x) < ans)
			ans = check(a, l, y, x), id = i+1;
	}
	printf("%d\n", id);
}
