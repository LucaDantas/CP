#include "Bruno.h"
#include <vector>
#include <cstdio>

namespace {

int tipo[3][3], mat[3][3];

bool valid(int a) { return a >= 0 && a <= 2; }

void fill(int r, int c) {
	for(int i = -2; i <= 2; i++) {
		for(int j = -2; j <= 2; j++) {
			if(valid(r+i) && valid(c+j))
				tipo[r+i][c+j] = (i+3)%3 + 3*((j+3)%3);
		}
	}
}

int get(int r, int c, int v) {
	r = 2-r; c = 2-c;
	int x = v%3, y = v/3;
	if(y > c) return 1;
	if(y < c) return 2;
	if(x > r) return 3;
	if(x < r) return 4;
	return 5;
}

}

std::vector<int> Bruno(int K, std::vector<int> value) {
	std::vector<int> ans(K, 0);
	for(int r = 0; r < 3; r++)
		for(int c = 0; c < 3; c++)
			if(value[3*r + c] == 14) {fill(r, c); break;}

	for(int r = 0; r < 3; r++)
		for(int c = 0; c < 3; c++)
			mat[r][c] = value[3*r + c];

	for(int r = 0; r < 3; r++) {
		for(int c = 0; c < 3; c++) {
			if(tipo[r][c] == 0 || tipo[r][c] == 8) continue;

			if(mat[r][c] < 5) ans[tipo[r][c]-1] = mat[r][c] - 1;
			else ans[tipo[r][c]-1] = get(r, c, mat[r][c] - 5) - 1;
		}
	}

	return ans;
}
