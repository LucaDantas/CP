#include <bits/stdc++.h>
using namespace std;

int n, K;
vector<int> sv[3];

int impar() {
	if(!sv[1].size()) return 0x3f3f3f3f;
	int ans = sv[1][0], ptr1 = 1, ptr2 = 0;
	int qtd = 1;
	for(; qtd < K; qtd += 2) {
		if(ptr1 >= (int)sv[1].size()-1 || ptr2 == (int)sv[2].size()) break;
		if(sv[1][ptr1] + sv[1][ptr1+1] < sv[2][ptr2])
			ans += sv[1][ptr1] + sv[1][ptr1+1], ptr1 += 2;
		else ans += sv[2][ptr2], ptr2++;
	}
	for(; qtd < K && ptr2 < (int)sv[2].size(); qtd += 2, ptr2++)
		ans += sv[2][ptr2];
	for(; qtd < K && ptr1 < (int)sv[1].size(); qtd++, ptr1++)
		ans += sv[1][ptr1];
	return ans;
}

int par() {
	int ans = 0, ptr1 = 0, ptr2 = 0;
	int qtd = 0;
	for(; qtd < K; qtd += 2) {
		if(ptr1 >= (int)sv[1].size()-1 || ptr2 == (int)sv[2].size()) break;
		if(sv[1][ptr1] + sv[1][ptr1+1] < sv[2][ptr2])
			ans += sv[1][ptr1] + sv[1][ptr1+1], ptr1 += 2;
		else ans += sv[2][ptr2], ptr2++;
	}
	for(; qtd < K && ptr2 < (int)sv[2].size(); qtd += 2, ptr2++)
		ans += sv[2][ptr2];
	for(; qtd < K && ptr1 < (int)sv[1].size(); qtd++, ptr1++)
		ans += sv[1][ptr1];
	return ans;
}

int main() {
	scanf("%d %d", &n, &K);
	for(int i = 0, d, t; i < n; i++)
		scanf("%d %d", &d, &t), sv[d].push_back(t);

	if(sv[1].size())
		sort(sv[1].begin(), sv[1].end());
	if(sv[2].size())
		sort(sv[2].begin(), sv[2].end());

	printf("%d\n", min(par(), impar()));
}