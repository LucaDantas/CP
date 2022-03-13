#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 410;

int village[maxn][maxn]; // represents whether there is a village
pair<int,int> pai[maxn][maxn]; // represents the edge it came from on the first dijsktra

int horizontal[maxn][maxn], vertical[maxn][maxn];
bool blue_h[maxn][maxn], blue_v[maxn][maxn];

int n, m;

long long dist[maxn][maxn];
bool mark[maxn][maxn];

// que negocio feio
void dijkstra1() {
	memset(dist, 0x3f, sizeof dist);
	dist[1][1] = 0;
	priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> q;
	q.push({0, 1, 1});

	while(q.size()) {
		auto [trash, x, y] = q.top(); q.pop();

		if(mark[x][y]) continue; mark[x][y] = 1;

		// [x][y] -> [x][y+1]
		if(y+1 <= m+1 && dist[x][y] + horizontal[x][y] < dist[x][y+1]) {
			dist[x][y+1] = dist[x][y] + horizontal[x][y];
			pai[x][y+1] = {x, y};
			q.push({dist[x][y+1], x, y+1});
		}
		// [x][y] -> [x][y-1]
		if(y-1 >= 1 && dist[x][y] + horizontal[x][y-1] < dist[x][y-1]) {
			dist[x][y-1] = dist[x][y] + horizontal[x][y-1];
			pai[x][y-1] = {x, y};
			q.push({dist[x][y-1], x, y-1});
		}
		// [x][y] -> [x+1][y]
		if(x+1 <= n+1 && dist[x][y] + vertical[x][y] < dist[x+1][y]) {
			dist[x+1][y] = dist[x][y] + vertical[x][y];
			pai[x+1][y] = {x, y};
			q.push({dist[x+1][y], x+1, y});
		}
		// [x][y] -> [x-1][y]
		if(x-1 >= 1 && dist[x][y] + vertical[x-1][y] < dist[x-1][y]) {
			dist[x-1][y] = dist[x][y] + vertical[x-1][y];
			pai[x-1][y] = {x, y};
			q.push({dist[x-1][y], x-1, y});
		}

	}
}

void go(int r, int c) {
	if(r == 1 && c == 1) return;
	if(pai[r][c] == pair<int,int>(r-1, c) && !blue_v[r-1][c]) {
		blue_v[r-1][c] = 1;
		go(r-1, c);
	} else if(pai[r][c] == pair<int,int>(r+1, c) && !blue_v[r][c]) {
		blue_v[r][c] = 1;
		go(r+1, c);
	} else if(pai[r][c] == pair<int,int>(r, c-1) && !blue_h[r][c-1]) {
		blue_h[r][c-1] = 1;
		go(r, c-1);
	} else if(pai[r][c] == pair<int,int>(r, c+1) && !blue_h[r][c]) {
		blue_h[r][c] = 1;
		go(r, c+1);
	}
}

void mark_blue() {
	// pinto os arredores de todas as vilas como azuis
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(village[i][j]) go(i, j); // pinto o menor caminho de mim até a raiz de azul

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(village[i][j]) {
				blue_h[i][j] = 1;
				blue_v[i][j] = 1;
				blue_h[i+1][j] = 1;
				blue_v[i][j+1] = 1;
			}
		}
	}

	// arestas especiais -> se eu nao colocar isso o cara pode simplesmente cruzar pelo canto superior esquerdo e a resposta vai ser 0
	blue_v[0][1] = 1;
	blue_h[1][0] = 1;
}

vector<pair<int,int>> g[4*maxn*maxn]; // meu indice é == 4*((i-1)*(m+1) + (j-1)) + id_quadrado

// id_quadrado:
// 00 == 0 -> left_up
// 01 == 1 -> right_up
// 10 == 2 -> left_down
// 11 == 3 -> right_down

void create_edges() {
	// arestas entre subpontos do mesmo ponto
	for(int i = 1; i <= n+1; i++) {
		for(int j = 1; j <= m+1; j++) {
			int id = 4*((i-1)*(m+1) + (j-1)); // id base pros proximos (vou somar id_qd pra obter o valor real)
			if(!blue_v[i-1][j]) // linha vindo de [i-1][j] -> [i][j]
				g[id].push_back({id+1, 0}), g[id+1].push_back({id, 0});
			
			if(!blue_v[i][j]) // linha [i][j] -> [i+1][j]
				g[id+2].push_back({id+3, 0}), g[id+3].push_back({id+2, 0});

			if(!blue_h[i][j-1]) // linha [i][j-1] -> [i][j]
				g[id].push_back({id+2, 0}), g[id+2].push_back({id, 0});

			if(!blue_h[i][j]) // linha [i][j] -> [i][j+1]
				g[id+1].push_back({id+3, 0}), g[id+3].push_back({id+1, 0});
		}
	}

	auto get = [](int i, int j) { return 4*((i-1)*(m+1) + (j-1)); };
	auto valid = [](int i, int j) { return i >= 1 && i <= n+1 && j >= 1 && j <= m+1; };

	// arestas entre subpontos de pontos diferentes (tem peso)
	for(int i = 1; i <= n+1; i++) {
		for(int j = 1; j <= m+1; j++) {
			int id = get(i, j);

			if(valid(i-1, j)) // [i-1][j] -> [i][j]
				g[id].push_back({get(i-1, j) + 2, vertical[i-1][j]}),
				g[id+1].push_back({get(i-1, j) + 3, vertical[i-1][j]});
			
			if(valid(i+1, j)) // [i][j] -> [i+1][j]
				g[id+2].push_back({get(i+1, j), vertical[i][j]}),
				g[id+3].push_back({get(i+1, j)+1, vertical[i][j]});
			
			if(valid(i, j-1)) // [i][j-1] -> [i][j]
				g[id].push_back({get(i, j-1)+1, horizontal[i][j-1]}),
				g[id+2].push_back({get(i, j-1)+3, horizontal[i][j-1]});

			if(valid(i, j+1)) // [i][j] -> [i][j+1]
				g[id+1].push_back({get(i, j+1), horizontal[i][j]}),
				g[id+3].push_back({get(i, j+1)+2, horizontal[i][j]});
		}
	}
}

long long dist2[maxn*maxn*4];
bool mark2[maxn*maxn*4];

void dijkstra2() {
	memset(dist2, 0x3f, sizeof dist2);
	priority_queue<pair<long long,int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

	dist2[1] = 0; // 1 é o quadrado superior direito de [1][1]
	
	q.push({0, 1});
	
	while(q.size()) {
		int u = q.top().second; q.pop();
		if(mark2[u]) continue; mark2[u] = 1;

		for(auto [v, w] : g[u]) {
			if(dist2[v] > dist2[u] + w) {
				dist2[v] = dist2[u] + w;
				q.push({dist2[v], v});
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &village[i][j]);

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m+1; j++)
			scanf("%d", &vertical[i][j]); // the edge from [i][j] to [i+1][j], [i][j] represents the top left square
	
	for(int i = 1; i <= n+1; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &horizontal[i][j]); // [i][j] to [i][j+1]

	dijkstra1();

	mark_blue();

	create_edges();

	dijkstra2();

	printf("%lld\n", dist2[2]);
}
