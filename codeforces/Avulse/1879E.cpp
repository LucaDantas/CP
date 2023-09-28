#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;

int p[maxn], cor[maxn], filhos[maxn], sub[maxn], qtd;

int main() {
    int n; scanf("%d", &n);
    bool duas = 0; // se eu preciso de duas cores ou nao
    for(int i = 2; i <= n; i++)
        scanf("%d", p+i), ++filhos[p[i]], duas |= p[i]>1, cor[i] = 1^cor[p[i]];
    if(!duas) {
        // pinto todo mundo da mesma cor
        qtd = 1;
        puts("1");
        for(int i = 2; i <= n; i++)
            printf("1 ");
        puts("");
    } else {
        int c[maxn][2]{};
        bool fudeu = 0;
        for(int i = 2; i <= n; i++) {
            if(p[i] == 1) sub[i] = i;
            else sub[i] = sub[p[i]];
            if(filhos[i] == 1) c[sub[i]][cor[i]] = 1;
            fudeu |= c[sub[i]][0] && c[sub[i]][1];
        }
        for(int i = 2; i <= n; i++)
            if(c[sub[i]][1])
                cor[i] ^= 1;
        if(fudeu) {
            // preciso de 3 cores
            qtd = 3;
            puts("3");
            for(int i = 2; i <= n; i++)
                cor[i] = (cor[p[i]]+1)%3, printf("%d ", cor[i] + 1);
            puts("");
        } else {
            // uso as cores dos caras pra fazer as arestas
            qtd = 2;
            puts("2");
            for(int i = 2; i <= n; i++)
                printf("%d ", cor[i] + 1);
            puts("");
        }
    }
    fflush(stdout);
    for(int op; scanf("%d", &op), !op; ) {
        vector<int> cnt(qtd);
        for(int& x : cnt)
            scanf("%d", &x);
        vector<int> unico;
        for(int i = 0; i < qtd; i++)
            if(cnt[i] == 1) unico.push_back(i);
        if(unico.size() == 1)
            printf("%d\n", unico.back() + 1);
        else if(qtd == 2)
            printf("%d\n", 1);
        else
            printf("%d\n", 1 + ((6 - unico.front() - unico.back() + 1) % 3));
        fflush(stdout);
    }
}
