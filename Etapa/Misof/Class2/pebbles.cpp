#include <cstdio>
#include <cassert>

int a[1010];

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0, last = 0, sv = 0; i < n; i++)
			scanf("%d", &a[i]), sv = a[i], a[i] -= last, last = sv;
		
		int x = 0;
		for(int i = n-1; i >= 0; i -= 2)
			x ^= a[i];

		if(!x) puts("Anicka");
		else {
			int pos = 0, val = 0;
			for(int i = n-1, pr = 1; i >= 0; i--, pr^=1) {
				if(pr && (a[i] & (1 << (31-__builtin_clz(x)))))
					pos = i+1, val = a[i] - (a[i]^x);
				else if(!pr && ((a[i+1]^x) > a[i+1] && a[i] >= (a[i+1]^x) - a[i+1]))
					pos = i+1, val = (a[i+1]^x) - a[i+1];
			}
			printf("Rasto %d %d\n", pos, val);
		}
	}
}
