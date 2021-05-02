#include "vision.h"
#include <bits/stdc++.h>
using namespace std;

// I need to check if the two points are at most k blocks far away
// from each other in one of the diagonals and exactly k in the other

constexpr int maxn = 410+10;

vector<int> diagonal[maxn][2]; // 1 == x+y, 2 == x-y+shift

int ok[2]; // checa se os pontos estao a uma distancia menor ou igual
// a K na dimensao respectiva (salva a posicao na memoria disso)

int ans_diag[maxn][2];

vector<int> tudo[2], resp;

void construct_network(int H, int W, int K) {
	for(int i = 0; i < H; i++) {
		for(int j = 0; j < W; j++) {
			diagonal[i+j][0].push_back(i*W + j);
			diagonal[i-j+W-1][1].push_back(i*W + j);
		}
	}
	for(int i = 0; i < H+W-1; i++) {
		for(int type : {0, 1}) {
			assert(diagonal[i][type].size());
			int v1 = ans_diag[i][type] = add_or(diagonal[i][type]);
			int v2 = add_xor(diagonal[i][type]);
			tudo[type].push_back(add_xor({v1, v2}));
		}
	}
	for(int i = 0; i < H+W-1; i++) {
		for(int type : {0, 1}) {
			vector<int> checar;
			for(int j = 0; j <= K && i + j < H+W-1; j++)
				checar.push_back(ans_diag[i+j][type]);
			int v1 = add_or(checar);
			int v2 = add_xor(checar);
			tudo[type].push_back(add_xor({v1, v2}));
		}
	}
	for(int type : {0, 1})
		ok[type] = add_or(tudo[type]);
	for(int i = 0; i < H+W-1; i++) {
		for(int type : {0, 1}) {
			if(i+K >= H+W-1) continue;
			vector<int> checar = {ans_diag[i][type], ans_diag[i+K][type]};
			int v1 = add_or(checar);
			int v2 = add_xor(checar);
			resp.push_back(add_and({add_xor({v1, v2}), ok[!type]}));
		}
	}
	add_or(resp);
}
