#include "dna.h"
#include <cassert>

constexpr int maxn = 1e5+10;

int a[maxn], b[maxn], pref[maxn][6], qtd[maxn][2][3], n;

int tp(char c) { return c == 'A' ? 0 : c == 'T' ? 1 : 2; }

int df(int a, int b) {
	if(a > b) return 5 - df(b, a);
	if(a == 0 && b == 1) return 0;
	if(a == 0 && b == 2) return 1;
	return 2; // [1, 2]
}

void init(std::string s1, std::string s2) {
	n = (int)s1.size();
	for(int i = 0; i < n; i++)
		a[i] = tp(s1[i]);
	for(int i = 0; i < n; i++)
		b[i] = tp(s2[i]);

	for(int i = 0; i < n; i++) {
		if(i) {
			for(int j = 0; j < 6; j++)
				pref[i][j] = pref[i-1][j];
			for(int j = 0; j < 3; j++)
				for(int k = 0; k < 2; k++)
					qtd[i][k][j] = qtd[i-1][k][j];
		}
		qtd[i][0][a[i]]++;
		qtd[i][1][b[i]]++;

		if(a[i] == b[i]) continue; // não adiciono em canto nenhum
		pref[i][df(a[i], b[i])]++;
	}
}

bool valid(int x, int y) {
	for(int k = 0; k < 3; k++)
		if(qtd[y][0][k] - (x ? qtd[x-1][0][k] : 0) != qtd[y][1][k] - (x ? qtd[x-1][1][k] : 0))
			return 0;
	return 1;
}

int get_distance(int x, int y) {
	if(!valid(x, y)) return -1;

	int val[6]{};
	for(int j = 0; j < 6; j++)
		val[j] = pref[y][j];
	if(x) for(int j = 0; j < 6; j++)
		val[j] -= pref[x-1][j];
	int ans = 0, sobra = 0;
	for(int j = 0; j < 3; j++) {
		int aq = std::min(val[j], val[5-j]);
		ans += aq;
		val[j] -= aq, val[5-j] -= aq;
		sobra += val[j] + val[5-j];
	}
	ans += (sobra / 3) * 2;
	assert(!(sobra%3));
	return ans;
}
