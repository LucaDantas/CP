#include "Anna.h"
#include <vector>
#include <cstdio>

namespace {
	std::vector<int> R, C;

	int get(int r, int c) { return r%3 + 3*(c%3); }
	int tipo(int r, int c) {
		int t = get(r, c);
		if(t == 0) return 14;
		if(t == 8) return 1;
		--t;

		if(C[t] > c+1) return 1;
		if(C[t] < c-1) return 2;
		if(R[t] > r+1) return 3;
		if(R[t] < r-1) return 4;

		return 5 + R[t] - (r-1) + 3 * (C[t] - (c-1));
	}
}

void Anna(int N, int K, std::vector<int> Ri, std::vector<int> Ci) {
	R = Ri;
	C = Ci;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			SetFlag(r, c, tipo(r, c));
		}
	}
}
