#include <bits/stdc++.h>
using namespace std;

class Solver {
public:
    Solver(int _N, int _K) : N(_N), K(_K), ans(0), g(N+1) {}

    void addEdge(int a, int b) { g[a].push_back(b), g[b].push_back(a); }

    int solve() {
        if(N == 2)
            return K == 1 ? 2 : 1;

        int start = 1;
        for(; g[start].size() == 1; start++);

        int ativo = dfs(start, 0) >= 0;
        return ans + ativo;
    }

private:
    int N, K, ans;

    vector<vector<int>> g;

    int dfs(int u, int p) { // retorna o valor do mais pesado
        vector<int> filhos;
        for(int v : g[u]) if(v != p)
            filhos.push_back(dfs(v, u) + 1);

        if(!filhos.size())
            return 0;

        sort(filhos.begin(), filhos.end(), greater<int>());

        while(filhos.size() >= 2 && filhos.back() + filhos[(int)filhos.size() - 2] <= K)
            filhos.pop_back();

        ans += (int) filhos.size() - 1;

        if(filhos.back() >= K) {
            ++ans;
            return -0x3f3f3f3f;
        }

        return filhos.back();
    }
};

int main() {
    int n, k; scanf("%d %d", &n, &k);
    Solver solver(n, k);
    for(int i = 1, a, b; i < n; i++)
        scanf("%d %d", &a, &b), solver.addEdge(a, b);
    
    printf("%d\n", solver.solve());
}
