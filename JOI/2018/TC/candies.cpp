#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

#define int long long

struct DSU {
    int pai[maxn], peso[maxn], l[maxn], r[maxn], val[maxn], filho[maxn]; // filho eh se tem algum do meu lado ativado
    void init(int a[]) { for(int i = 0; i < maxn; i++) pai[i] = l[i] = r[i] = i, peso[i] = 1, val[i] = a[i]; }
    int find(int x) { return pai[x] == x ? x : pai[x] = find(pai[x]); }
    void merge_dsu(int a, int b) {
        a = find(a), b = find(b);
        if(peso[a] < peso[b])
            swap(a, b);
        pai[b] = a;
        peso[a] += peso[b];
        l[a] = min(l[a], l[b]);
        r[a] = max(r[a], r[b]);
    }
    void merge(int p, int f1, int f2) {
        // nao eh pra precisar dar find nessa funcao, isso eu farei antes de chamar pros caras necessarios
        int new_val = val[f1] + val[f2] - val[p];
        // filho nao sobe, sempre ta salvo no do pai e eh usado quando vai dar merge, entao n faz nada com ele
        merge_dsu(p, f1);
        merge_dsu(p, f2);
        int raiz = find(p);
        val[raiz] = new_val;
        filho[raiz] = 0; // nao tem mais nenhum filho, deu merge
    }
    bool set_filho(int colocar, int p) { // retorna true se deu merge
        colocar = find(colocar), p = find(p);
        if(!filho[p])
            return (filho[p] = colocar, false);

        int f2 = find(filho[p]);
        merge(p, colocar, f2);

        return true;
    }
} dsu;

int a[maxn];

bool disponiveis[maxn];

priority_queue<pair<int,int>> q;

int32_t main() {
    int n; scanf("%lld", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lld", a+i), q.push({a[i], i});

    memset(disponiveis, 1, sizeof disponiveis);

    dsu.init(a);

    long long ans = 0;
    while(q.size()) {
        auto [val, colocar] = q.top();
        q.pop();
        colocar = dsu.find(colocar);
        int l = dsu.l[colocar], r = dsu.r[colocar];
        if(disponiveis[l-1] && disponiveis[r+1]) {
            ans += dsu.val[colocar];
            disponiveis[l] = disponiveis[r] = 0;
            printf("%lld\n", ans);
            continue;
        }
        int k = disponiveis[l-1] ? r+1 : l-1; // sei com certeza que pelo menos um deles ta disponivel
        if(dsu.set_filho(colocar, k)) {
            // ja consegui dar um merge, nem continuo pra colocar filho no outro, so recoloco ele na fila e fds
            colocar = dsu.find(colocar);
            q.push({dsu.val[colocar], colocar});
        }
    }
}
