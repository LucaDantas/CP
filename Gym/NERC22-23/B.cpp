#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1010, maxk = 101;

vector<int> seq[maxk];

pair<int,int> f[maxn]; // filhos de i

int p[maxn];

vector<int> vivos;

const pair<int,int> trash = {-1, -1};

bool comp(const pair<int,int>& a, pair<int,int> b) { bool ok = a == b; swap(b.first, b.second); return ok || a == b; }

bool mark[maxn];

int main() {
    memset(p, -1, sizeof p);
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 1; i <= k; i++) {
        seq[i].resize(n+2);
        for(int j = 1; j <= n; j++)
            scanf("%d", &seq[i][j]);
        seq[i][0] = -1;
        seq[i][n+1] = -2;
    }
    int org_n = n;
    vivos.resize(n);
    iota(vivos.begin(), vivos.end(), 1);
    while(n > 1) { // eu mudo n pra vivo.size() no final sempre

        for(int j = 2; j < n; j++)
            f[seq[1][j]] = {seq[1][j-1], seq[1][j+1]};
        f[seq[1][1]] = f[seq[1][n]] = trash;

        for(int i = 2; i <= k; i++)
            for(int j = 1; j <= n; j++)
                if(!comp(f[seq[i][j]], pair<int,int>(seq[i][j-1], seq[i][j+1])))
                    f[seq[i][j]] = trash;
        
        for(int x : vivos)
            if(f[x] != trash)
                p[f[x].first] = x, p[f[x].second] = x, mark[f[x].first] = mark[f[x].second] = 1;

        for(int i = 1; i <= k; i++) {
            vector<int> aux = {-1};
            for(int j = 1; j <= n; j++)
                if(!mark[seq[i][j]])
                    aux.push_back(seq[i][j]);
            aux.push_back(-2);
            seq[i] = aux;
        }

        vector<int> aux;
        for(int x : vivos)
            if(!mark[x]) aux.push_back(x);
        vivos = aux;

        n = (int)(vivos.size());
    }
    for(int i = 1; i <= org_n; i++)
        printf("%d ", p[i]);
    puts("");
}
