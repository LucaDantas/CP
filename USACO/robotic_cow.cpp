#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

constexpr int maxn = 1e5+10;

std::vector<int> a[maxn];

struct ST
{
	long long a; int b, c;
	bool operator>(ST S) { return a > S.a; }
};

std::priority_queue<ST, std::vector<ST>, std::greater<>> q;

FILE *in, *out;

int main() {
	in = fopen("roboherd.in", "r");
	out = fopen("roboherd.out", "w");
	int n, k; fscanf(in, "%d %d", &n, &k);
	long long S = 0;
	std::vector<int> ind;
	for(int i = 0, m; i < n; i++) {
		fscanf(in, "%d", &m);
		a[i].resize(m);
		for(int j = 0; j < m; j++)
			fscanf(in, "%d", &a[i][j]);
		std::sort(a[i].begin(), a[i].end());
		S += (long long)a[i][0];
		if(m > 1) ind.push_back(i);
	}
	std::sort(ind.begin(), ind.end(), [](int x, int y) {
		return a[x][1] - a[x][0] < a[y][1] - a[y][0];
	});
	if(!(--k)) return fprintf(out, "%lld\n", S), 0;
	q.push({S + a[ind[0]][1] - a[ind[0]][0], 0, 1});
	while(k--) {
		auto [sum, i, j] = q.top(); q.pop();
		S += sum;
		if(j < (int)a[ind[i]].size() - 1)
			q.push({sum + a[ind[i]][j+1] - a[ind[i]][j], i, j+1});
		if(i < (int)ind.size()-1)
			q.push({sum + a[ind[i+1]][1] - a[ind[i+1]][0], i+1, 1});
		if(i < (int)ind.size()-1 && j == 1)
			q.push({sum - (a[ind[i]][1] - a[ind[i]][0]) + a[ind[i+1]][1] - a[ind[i+1]][0], i+1, 1});
	}
	fprintf(out, "%lld\n", S);
}