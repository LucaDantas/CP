#include <cstdio>
#include <cstring>

constexpr int maxn = 1e5+10, maxs = 1010;

int min(int a, int b) { return a < b ? a : b; }

bool a[maxn][maxs], aux[maxs];
int val[maxn], s, ans = 0x3f3f3f3f;

void add(bool vt[], int v) {
	for(int i = s-v; i >= 0; i--)
		vt[i+v] |= vt[i];
}

bool check(bool vt[]) {
	for(int i = 0; i <= s; i++)
		if(vt[i] && aux[s-i]) return 1;
	return 0;
}

void cp(bool src[], bool dest[]) {
	for(int i = 0; i <= s; i++)
		dest[i] = src[i];
}

int main() {
	int n; scanf("%d %d", &n, &s);
	for(int i = 0; i < n; i++)
		scanf("%d", val+i);

	aux[0] = 1;
	int meio = 0;
	for(; meio < n && !aux[s]; meio++)
		add(aux, val[meio]);

	int ptr = meio, start = 0;

	for(; start < n;) {
		memset(aux, 0, sizeof aux);
		aux[0] = 1;

		a[meio][0] = 1;
		for(int i = meio-1; i >= start; i--)
			cp(a[i+1], a[i]), add(a[i], val[i]);

		for(int i = start; i < meio; i++) {
			for(; ptr < n && !check(a[i]); ++ptr)
				add(aux, val[ptr]);
			if(ptr < n || check(a[i])) ans = min(ans, ptr - i); 
			else break;
		}

		start = meio;
		meio = ptr;
	}

	printf("%d\n", ans < 0x3f3f3f3f ? ans : -1);
}
