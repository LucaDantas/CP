#include<bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d", &t);
	while(t--) {
		int n; scanf("%d", &n);
		for(int i = 0; i < n; i++)
			printf("%d ", 2*n+2*i);
		printf("\n");
	}
}