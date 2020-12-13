#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10, logn = 20;

int path[maxn][logn+1], last[maxn], pos;
int let[maxn], qtd[maxn], tam[maxn];

void Init() {}

void TypeLetter(char L) {
	++pos;
	qtd[pos] = qtd[last[pos-1]] + 1;
	tam[pos] = tam[last[pos-1]] + 1;
	last[pos] = pos;
	let[pos] = L-'a';
	path[pos][0] = last[pos-1];
	for(int l = 1, p = last[pos-1]; l <= logn; l++) {
		path[pos][l] = path[p][l-1];
		p = path[p][l-1];
	}
}

void UndoCommands(int U) {
	++pos;
	last[pos] = last[pos-U-1];
}

char GetLetter(int P) {
	int p = last[pos];
	P = tam[p] - P - 1;
	for(int l = logn; l >= 0; l--)
		if(P >= (1 << l)) p = path[p][l], P -= 1<<l;
	return char(let[p]+'a');
}
