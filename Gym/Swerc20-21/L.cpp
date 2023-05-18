#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int n, m;

int sz[maxn]; // capacidade do restaurante

vector<pair<int,int>> c[maxn]; // rank dos restaurantes pelo ponto de vista do cliente e com o valor que o rest deu pro cliente
vector<int> r[maxn]; // rank dos clientes pelo ponto de vista do restaurante
int match_c[maxn]; // indice do restaurante que o consumidor ta ligado
set<pair<int,int>> match_r[maxn]; // valor e indices dos consumidores que o restaurante ta ligado

void go(int i) {
    for(auto [j, val] = c[i][match_c[i]]; match_c[i] < (int)c[i].size(); tie(j, val) = c[i][++match_c[i]]) {
        // i eh o consumidor
        // j eh o restaurante
        if((int)match_r[j].size() < sz[j])
            return (void)(match_r[j].insert({val, i}));

        if(match_r[j].rbegin()->first > val) {
            match_r[j].insert({val, i});
            tie(val, i) = *match_r[j].rbegin();
            match_r[j].erase({val, i});
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= m; i++)
        scanf("%d", sz+i);

    for(int i = 1; i <= n; i++) {
        int val; char ch = ' ';
        for(int j = 0; ch != '\n'; j++) {
            scanf("%d%c", &val, &ch);
            c[i].push_back({val, 0});
        }
    }

    map<pair<int,int>, int> mp;
    for(int i = 1; i <= m; i++) {
        int val; char ch = ' ';
        for(int j = 0; ch != '\n'; j++) {
            scanf("%d%c", &val, &ch);
            r[i].push_back(val);
            mp[{val, i}] = j;
        }
    }

    for(int i = 1; i <= n; i++)
        for(auto& [rest, val] : c[i])
            val = mp[{i, rest}];
    
    for(int i = 1; i <= n; i++)
        go(i);

    for(int i = 1; i <= n; i++)
        if(match_c[i] < (int)c[i].size())
        printf("%d\n", i);
}