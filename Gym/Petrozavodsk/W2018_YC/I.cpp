#include <cstdio>
#include <cassert>
#include <cstring>
#include <map>

constexpr int maxn = 1e4+10;

int a[maxn], b[maxn];
std::map<int,int> v;

const char geq[4] = ">=", leq[4] = "<=", fim[4] = "End";

int main() {
	int n, k; scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++)
		scanf("%d", &b[i]), a[i] = 1<<(k-1);
	for(int rep = 0; rep < 50; rep++) {
		v.clear();
		int val = 0;
		for(int i = 0; i < n; i++)
			val += a[i], v[b[i]] += a[i];
		if(!val) break;

		int qr = -1, now = 0;
		for(auto x : v) {
			now += x.second;
			if((now << 1) >= val) {
				qr = x.first;
				break;
			}
		}
		assert(qr != -1);

		printf("%d\n", qr); fflush(stdout);

		char op[4];
		scanf("%s", op);
		if(strcmp(op, fim) == 0) break;

		assert(strcmp(op, geq) == 0 || strcmp(op, leq) == 0);

		bool ok = 0;
		if(strcmp(op, geq) == 0) ok = 1;
		
		for(int i = 0; i < n; i++) {
			if((ok && b[i] >= qr) || (!ok && b[i] <= qr))
				a[i] >>= 1;
			scanf("%d", &b[i]);
		}
	}
}
