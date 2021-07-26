#include <bits/stdc++.h>
using namespace std;

int pot[15];
int vl(int x) { return x == 0 ? -1 : x == 1 ? 1 : 0; }

int main() {
	int t; scanf("%d", &t);
	pot[0] = 1;
	for(int i = 1; i <= 10; i++)
		pot[i] = pot[i-1] * 3;
	while(t--) {
		int n; scanf("%d", &n);
		vector<int> a(n);

		for(int& x : a)
			scanf("%d", &x), x = x < 0 ? -x : x;
	
		sort(a.begin(), a.end());
		
		a.resize(unique(a.begin(), a.end()) - a.begin());
		if((int)a.size() != n) { puts("Yes"); continue; }
		
		bool ok = a[0] == 0;

		for(int k = 0; k < n; k++) {
			for(int i = 0; i < pot[n-1]; i++) {
				int hm = i, soma = 0;
				for(int j = 0; j < n; j++) if(j != k)
					soma += vl(hm%3) * a[j], hm /= 3;
				ok |= soma == a[k];
			}
		}
		
		puts(ok ? "Yes" : "No");
	}
}

