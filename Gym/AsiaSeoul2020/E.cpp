#include<cstdio>

int main() {
	int n, state = 0; scanf("%d", &n);
	while(n--) {
		int v; scanf("%d", &v);
		if(v == 1) state ^= 1;
		else if(v > 2 || (v == 2 && !state)) return puts("NO"), 0;
	}
	puts(!state?"YES":"NO");
}