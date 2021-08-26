#include "doll.h"
#include <algorithm>
#include <cstdio>

constexpr int inf = 0x3f3f3f3f;

int x[400010], y[400010], state[400010], cnt = 1, fim, pos[400010];

void solve(int id, int pot, int N) {
	if(N == 1 && pot == 0) return (void)(x[id] = -1, y[id] = inf);
	if(N == 2 && pot == 0) return (void)(x[id] = inf, y[id] = inf);
	
	if(N > (1 << pot)) {
		x[id] = -(++cnt);
		int aq = N - (1 << pot);
		solve(-x[id], pot-1, aq);
	} else x[id] = -1;

	y[id] = -(++cnt);
	solve(-y[id], pot-1, std::min(N, 1<<pot));
}

std::vector<int> a;

void go(int u) {
	if(fim == (int)(a.size())) return;
	int& vai = state[u] ? y[u] : x[u];
	state[u] ^= 1;
	if(vai == inf) return (void)(vai = a[fim++], go(1));
	go(-vai);
}

void create_circuit(int M, std::vector<int> A) {
	int N = (int)(A.size());
	if(N == 1) return answer({1, 0}, {}, {});
	
	std::vector<int> C(M + 1);
	C[0] = A[0];

	A.push_back(0);
	A.erase(A.begin());
	a = A;

	for(int i = 1; i <= M; ++i)
		C[i] = -1;
	
	solve(1, 31-__builtin_clz(N)-(__builtin_popcount(N) == 1), N);
	
	std::vector<int> X(cnt), Y(cnt);
	for(int i = 1; i <= cnt; i++)
		X[i-1] = x[i], Y[i-1] = y[i];

	go(1);

	for(int i = 1; i <= cnt; i++)
		X[i-1] = x[i], Y[i-1] = y[i];
	
	answer(C, X, Y);
}
