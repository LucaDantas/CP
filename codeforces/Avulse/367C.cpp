#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, m; scanf("%d %d", &n, &m);
	vector<int> val(m);
	for(int i = 0; i < m; i++) {
		int trash; scanf("%d %d", &trash, &val[i]);
	}
	sort(val.rbegin(), val.rend());
	int qtd = 1;
	while(1) {
		if(qtd * (qtd-1) / 2 < n) qtd++;
		else break;
		if(qtd * (qtd-1) / 2 + (qtd/2)-1 < n) qtd++;
		else break;
	}
	qtd--;
	int ans = 0;
	for(int i = 0; i < min(qtd, m); i++)
		ans += val[i];
	printf("%d\n", ans);
}