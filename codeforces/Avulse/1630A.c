#include <stdio.h>

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n, k; scanf("%d %d", &n, &k);
		if(!k) {
			for(int i = 0; i < n/2; i++) printf("%d %d\n", i, n-1-i);
		} else if(k == n-1) {
			if(n == 4) { puts("-1"); continue; }

			printf("%d %d\n", k, k-1);
			puts("1 3");
			printf("%d %d\n", k-3, 0);

			printf("2 %d\n", k-2);

			for(int i = 4; i < n/2; i++)
				printf("%d %d\n", i, k-i);
		} else {
			printf("%d %d\n%d %d\n", k, n-1, (n-1)^k, 0);
			for(int i = 1; i < n/2; i++)
				if(i != k && i != ((n-1)^k)) printf("%d %d\n", i, (n-1)^i); 
		}
	}
}
