#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

constexpr int maxn = 2e5+10;

struct Frac {
	int a, b;
	Frac(int _a = 0, int _b = 1) : a(_a), b(_b) {}
	bool operator>=(const Frac& o) const { return 1ll*a*o.b >= 1ll*o.a*b; }
} ANS;

vector<int> sv_ans;

int m[maxn], k[maxn];

int val[maxn][21];

vector<pair<int,int>> hm[21];

int main() {
	int n; scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d %d", m+i, k+i);
	for(int i = 0; i < n; i++)
		for(int qtd = 1; qtd <= 20; qtd++)
			val[m[i]][qtd] += min(k[i], qtd);
	for(int qtd = 1; qtd <= 20; qtd++) {
		for(int i = 1; i < maxn; i++)
			if(val[i][qtd]) hm[qtd].push_back({val[i][qtd], i});
		sort(hm[qtd].begin(), hm[qtd].end());
		reverse(hm[qtd].begin(), hm[qtd].end());
		int aq = 0;
		vector<int> sv_aq;
		for(int i = 0; i < min(qtd, (int)(hm[qtd].size())); i++)
			aq += hm[qtd][i].first, sv_aq.push_back(hm[qtd][i].second);
		if(Frac(aq, qtd) >= ANS)
			ANS = Frac(aq, qtd), sv_ans = sv_aq;
	}
	printf("%ld\n", sv_ans.size());
	for(int x : sv_ans)
		printf("%d ", x);
	puts("");
}
