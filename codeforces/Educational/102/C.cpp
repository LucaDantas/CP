#include<bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
       	while(t--) {
		int n, k; scanf("%d %d", &n, &k);
		for(int i = 1; i < 2*k-n; i++)
			printf("%d ", i);
		int x = k;
		for(int i = 2*k-n; i <= k; i++)
			printf("%d ", x--);
		puts("");
	}
}

