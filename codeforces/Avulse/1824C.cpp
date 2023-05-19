#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5+10;

int a[maxn];

vector<int> g[maxn];

struct ST {
    map<int,int> cnt;
    int x = 0; // valor que tira o xor com todo o set pra achar o real valor
    int cost = 0;
    int mx_cnt = 0;
    void insert(int val) {
        val ^= x;
        ++cnt[val];
        mx_cnt = max(mx_cnt, cnt[val]);
    }
    void add_cost(int c) { cost += c; }
    void reduce() {
        cost -= mx_cnt; // quantos caras repetidos eu salvei pra usar esse valor

        if(mx_cnt == 1) return; // then I don't do anything
        for(auto it = cnt.begin(); it != cnt.end(); )
            if(it->second == mx_cnt) it->second = 1, ++it;
            else it = cnt.erase(it);

        mx_cnt = 1;
    }
    vector<int> get() {
        vector<int> ans;
        for(auto it : cnt)
            ans.push_back(it.first^x);
        return ans;
    }
    int sz() { return (int)(cnt.size()); }

    void debug(int u) {
        printf("u %d -> (x: %d) (cost: %d) (mx_cnt: %d)\n", u, x, cost, mx_cnt);
        for(auto it : cnt)
            printf("(%d %d) ", it.first, it.second);
        puts("");
    }
} st[maxn];

void dfs(int u, int p) {
    if(p) g[u].erase(find(g[u].begin(), g[u].end(), p));

    if(!g[u].size()) // leaf, base case
        return (void)(st[u].insert(a[u]));

    for(int& v : g[u]) {
        dfs(v, u);
        if(st[v].sz() > st[g[u].front()].sz())
            swap(v, g[u].front()); // o filho grande eh o primeiro
    }
    // faco o small to large
    swap(st[u], st[g[u].front()]);
    ++st[u].cost;

    // coloco o cara q eu ja juntei no final pra poder dar pop_back e iterar pelo resto mais facil
    swap(g[u].front(), g[u].back());
    g[u].pop_back();

    for(int v : g[u]) {
        st[u].cost += st[v].cost + 1; // coloco +1 porque em tese todo mundo tem q ser mudado pro valor final, mas no final eu subtraio os q n mudam
        for(const int& x : st[v].get())
            st[u].insert(x);
    }

    st[u].x ^= a[u];

    st[u].reduce();
}

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a+i);
    for(int i = 1, x, y; i < n; i++)
        scanf("%d %d", &x, &y), g[x].push_back(y), g[y].push_back(x);
    dfs(1, 0);
    printf("%d\n", st[1].cost + !st[1].cnt.count(st[1].x)); // if there is no 0 in the final set then I need to change the root for that value
}
