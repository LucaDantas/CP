#include "wombats.h"
#include <cstring>

constexpr int maxm = 205, maxn = 5010, inf = 0x3f3f3f3f, SZ = 11;

struct Node
{
	int dp[maxm][maxm];
	Node() { memset(dp, 0, sizeof dp); }
};

int min(int a, int b) { return a < b ? a : b; }

int H[maxn][maxm], V[maxn][maxm];
int N, m, qtd_blocks;

void calc(int linha, Node& ans) {
	static int dp[SZ+1][maxm];
	int tam = min(SZ, N - linha);

	for(int coluna = 0; coluna < m; coluna++) {
		memset(dp, 0x3f, sizeof dp);

		dp[0][coluna] = 0;
		
		for(int i = 0; i < tam; i++) {
			for(int j = 1; j < m; j++)
				dp[i][j] = min(dp[i][j], dp[i][j-1] + H[i + linha][j-1]);

			for(int j = m-2; j >= 0; j--)
				dp[i][j] = min(dp[i][j], dp[i][j+1] + H[i + linha][j]);

			if(i < tam-1)
				for(int j = 0; j < m; j++)
					dp[i+1][j] = dp[i][j] + V[i + linha][j];
		}

		for(int i = 0; i < m; i++)
			ans.dp[coluna][i] = dp[tam-1][i];
	}
}

void merge(Node L, Node R, Node& ans) {
	auto get = [&](int INI, int FIM, int l, int r) {
		int ans = inf, opt = l;
		for(int i = l; i <= r; i++) {
			if(L.dp[INI][i] + R.dp[i][FIM] < ans)
				ans = L.dp[INI][i] + R.dp[i][FIM], opt = i;
		}
		return opt;
	};

	for(int inicio = 0; inicio < m; inicio++)
		for(int i = 0, j = m-1-inicio; j < m; i++, j++)
			ans.dp[i][j] = get(i, j, i ? ans.dp[i-1][j] : 0, j<m-1 ? ans.dp[i][j+1] : m-1);
	for(int inicio = 1; inicio < m; inicio++)
		for(int i = inicio, j = 0; i < m; i++, j++)
			ans.dp[i][j] = get(i, j, i ? ans.dp[i-1][j] : 0, j<m-1 ? ans.dp[i][j+1] : m-1);
	
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++)
			ans.dp[i][j] = L.dp[i][ans.dp[i][j]] + R.dp[ans.dp[i][j]][j];
}

struct SegmentTree
{
	Node tree[1<<10];
	void build(int node, int i, int j) {
		if(i == j) return (void)(calc(i*(SZ-1), tree[node]));
		int m = (i+j) >> 1;
		build(node<<1, i, m); build(node<<1|1, m+1, j);
		merge(tree[node<<1], tree[node<<1|1], tree[node]);
	}
	int query(int l, int r) { return tree[1].dp[l][r]; }
	void upd(int node, int i, int j, int pos) {
		if(i == j) return (void)(calc(i*(SZ-1), tree[node]));
		int m = (i+j) >> 1;
		if(pos <= m) upd(node<<1, i, m, pos);
		else upd(node<<1|1, m+1, j, pos);
		merge(tree[node<<1], tree[node<<1|1], tree[node]);
	}
} seg;

void init(int R, int C, int hor[5000][200], int ver[5000][200]) {
    m = C; N = R;
    for(int i = 0; i < N; i++)
    	for(int j = 0; j < m-1; j++)
    		H[i][j] = hor[i][j];
    for(int i = 0; i < N-1; i++)
    	for(int j = 0; j < m; j++)
    		V[i][j] = ver[i][j];

    qtd_blocks = (N-1) / (SZ-1);

    seg.build(1, 0, qtd_blocks);
}

void changeH(int P, int Q, int W) {
    H[P][Q] = W;
    seg.upd(1, 0, qtd_blocks, P / (SZ-1));
    if(P % (SZ-1) == 0 && P)
    	seg.upd(1, 0, qtd_blocks, P / (SZ-1) - 1);
}

void changeV(int P, int Q, int W) {
    V[P][Q] = W;
    seg.upd(1, 0, qtd_blocks, P / (SZ-1));
}

int escape(int V1, int V2) {
    return seg.query(V1, V2);
}
