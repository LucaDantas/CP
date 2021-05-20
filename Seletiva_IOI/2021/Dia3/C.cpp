#include <bits/stdc++.h>
using namespace std;

struct CMD
{
	int tem, le, d, novo, esc;
	void print() {
		printf("%d %d %d %d %d\n", tem, le, d, novo, esc);
	}
};

int main() {
	int n; scanf("%d", &n); assert(n == 500);
	// divido em blocos de tamanho 25
	// 1, 2, 3, 4, ... 24 -> comandos de explorar (andar pra direita)
	// 25 -> comando de que chegou em uma marcação, marca 100, voltar pra o ultimo marcado com o comando 26
	// 26 -> anda pra esquerda quando o chao for 0 e quando for > 0 comeca a andar pra direita com o tipo que encontrou
	// 50 .. 90 -> anda pra direita até achar um 100, quando acha pinta o 100 do seu valor e continua pra direita com 0

	vector<CMD> cmd;
	cmd.push_back({1, 1, 1, 2, 0}); // subtask 2
	// comando 0 é especial e marca com o valor 50 e anda pra direita comecando no 2
	cmd.push_back({0, 0, 1, 2, 50});
	for(int i = 1; i <= 24; i++)
		cmd.push_back({i, 0, 1, i+1, 0});
	// comando 25
	cmd.push_back({25, 0, -1, 26, 100});
	// comando 26
	cmd.push_back({26, 0, -1, 26, 0});
	for(int i = 50; i < 71; i++)
		cmd.push_back({26, i, 1, i+1, i});
	for(int i = 50; i < 71; i++) {
		cmd.push_back({i, 0, 1, i, 0});
		cmd.push_back({i, 100, 1, 1, i});
	}
	printf("%ld\n", cmd.size()+1);
	for(auto p : cmd)
		p.print();
	// resposta
	puts("71 0 0");
}