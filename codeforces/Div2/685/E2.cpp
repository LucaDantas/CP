#include<bits/stdc++.h>
using namespace std;

int main() {
	int n; scanf("%d", &n);
	vector<int> a(n), pos(n, -1);
	int special = -1; pos[0] = 0;
	for(int i = 1; i < n; i++) {
		printf("XOR 1 %d\n", i+1); fflush(stdout);
		scanf("%d", &a[i]);
		if(special == -1 && pos[a[i]] != -1) {
			printf("AND %d %d\n", i+1, pos[a[i]]+1); fflush(stdout);
			scanf("%d", &special);
			special ^= a[i];
		} else pos[a[i]] = i;
	}
	if(special == -1) {
		printf("AND 1 %d\n", pos[1]+1); fflush(stdout);
		scanf("%d", &special);
		printf("AND 1 %d\n", pos[n-2]+1); fflush(stdout);
		int oto; scanf("%d", &oto);
		special |= oto&1;
	}
	printf("!");
	for(int i = 0; i < n; i++)
		printf(" %d", a[i]^special);
	printf("\n");
}