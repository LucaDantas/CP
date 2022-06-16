#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50010, inf = 0x3f3f3f3f;

int A[maxn], B[maxn], R, C;

int find_first_A(int id, int val) { int i; for(i = id+1; A[i] < val; i++); return i; }
int find_first_B(int id, int val) { int i; for(i = id+1; B[i] < val; i++); return i; }

int find_last_A(int id, int val) { int i; for(i = id-1; A[i] < val; i--); return i; }
int find_last_B(int id, int val) { int i; for(i = id-1; B[i] < val; i--); return i; }

int find_first(int lim_id, int lim_val, bool k) { return k == 0 ? find_first_A(lim_id, lim_val) : find_first_B(lim_id, lim_val); }
int find_last(int lim_id, int lim_val, bool k) { return k == 0 ? find_last_A(lim_id, lim_val) : find_last_B(lim_id, lim_val); }

long long go(int r, int c, bool k, bool st = 0) {
	int procurar = k == 0 ? r : c, eu = k == 0 ? c : r;
	int p1 = find_last(procurar, k == 0 ? B[eu] : A[eu], k), d1 = procurar - p1, v1 = k == 0 ? A[p1] : B[p1]; // ultimo cara vertical com indice menor que c e valor maior que A[r]
	int p2 = find_first(procurar, k == 0 ? B[eu] : A[eu], k), d2 = p2 - procurar, v2 = k == 0 ? A[p2] : B[p2]; // primeiro cara vertical com indice maior que c e valor maior que A[r]
	
	if(v1 > v2) // quero manter a invariante de que v1 < v2 pra ficar mais fácil de calcular as coisas
		swap(p1, p2), swap(d1, d2), swap(v1, v2);

	// subtraio 1 dos infinitos porque eu defini eles como o primeiro ponto fora do grid (0 ou R+1/C+1), então a distância deles fica 1 a mais doq pode
	if(v1 == inf)
		return max(d1, d2)-1; // cheguei ao fim indo pra algum dos lados, escolho o maior obviamente
	if(v2 == inf)
		return max(d1 + (k == 0 ? go(p1, c, 1) : go(r, p1, 0)), (long long) d2-1); // cheguei ao fim indo pro maior mas não cheguei indo pro menor, então pego o melhor entre os dois

	int down = find_first(eu, v1, !k), dist_down = down - eu, v_down = k == 0 ? B[down] : A[down]; // primeiro cara abaixo de mim (row index > r) com valor > v1
	int up = find_last(eu, v1, !k), dist_up = eu - up, v_up = k == 0 ? B[up] : A[up];

	if(B[down] > B[up])
		swap(down, up), swap(dist_down, dist_up), swap(v_down, v_up);

	// brutao pq meu guloso ta dando errado
	if(st) // na primeira rodada eu vou pros dois lados
		return max((long long) d1 + (k == 0 ? go(p1, c, !k) : go(r, p1, !k)), (long long) d2 + (k == 0 ? go(p2, c, !k) : go(r, p2, !k)));

	if(B[down] < v2 || d1 >= d2) {
		// nesse caso ou o p1 tem algum vizinho melhor que o p2 ou eles tem os mesmo vizinhos mas se eu for pro p1 eu ando mais, entao vou pro p1
		return (long long) d1 + (k == 0 ? go(p1, c, !k) : go(r, p1, !k));
	}
	// nesse caso o p1 e o p2 tem os mesmo vizinhos mas o p2 é mais longe entao vou pra ele
	return (long long) d2 + (k == 0 ? go(p2, c, !k) : go(r, p2, !k));
}

int main() {
	int q; scanf("%d %d %d", &R, &C, &q);
	for(int i = 1; i <= R; i++)
		scanf("%d", &A[i]);
	for(int i = 1; i <= C; i++)
		scanf("%d", &B[i]);
	A[0] = A[R+1] = B[0] = B[C+1] = inf;
	while(q--) {
		int r, c; scanf("%d %d", &r, &c);
		// printf("%lld\n", go(r, c, 0));
		printf("%lld\n", max(go(r, c, 0, 1), go(r, c, 1, 1)));
	}
}
