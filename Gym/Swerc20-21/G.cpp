#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, maxn = N;
constexpr long long inf = 1e12L+10;

vector<bool> used(N);
vector<int> ndiv(N, 1);

void calc() {
    for (int i = 2; i < N; i++) {
        if (!used[i]) {
            for (int j = i; j < N; j+=i) {
                used[j] = true;
                int temp = j;
                int cnt = 0;
                while(temp%i==0) {
                    temp/=i;
                    cnt++;
                }
                ndiv[j] *= (cnt + 1);
            }
        }
    }
}

int f[maxn], dist[maxn], sz[maxn], id[maxn], t;
int mark[maxn];

void paint(int u) {
    dist[u] = 0;
    id[u] = t;
    sz[t]++;
    if(dist[f[u]] == -1)
        paint(f[u]);
}

void find_cycle(int u) {
    if(mark[f[u]] == 2) return;
    mark[u] = 1;
    if(mark[f[u]])
        ++t, paint(f[u]);
    else
        find_cycle(f[u]);
    mark[u] = 2;
}

int get_dist(int u) {
    if(dist[u] != -1) return dist[u];
    dist[u] = get_dist(f[u]) + 1;
    id[u] = id[f[u]];
    return dist[u];
}

int main() {
    memset(dist, -1, sizeof dist);
    calc();
    int n, k;
    cin >> n >> k;
    
    vector<vector<int> > tra(21, vector<int>(n+1));
    tra[0][0] = n;
    tra[0][n] = n;
    for (int i = 1; i < n; i++) {
        tra[0][i] = (i + ndiv[i]) % n;
        f[i] = tra[0][i];
    }

    for(int i = 0; i <= n; i++)
        if(!mark[i]) find_cycle(i);
    for(int i = 0; i <= n; i++)
        get_dist(i);

    vector<vector<long long> > wei(21, vector<long long>(n+1));
    for (int i = 0; i < n; i++) wei[0][i] = i;
    wei[0][n] = inf;

    for (int i = 1; i <= 20; i++) {
        for (int j = 0; j <= n; j++) {
            tra[i][j] = tra[i-1][tra[i-1][j]];
            wei[i][j] = wei[i-1][j] + wei[i-1][tra[i-1][j]];
        }
    }

    vector<long long> ans(n+1);
    vector<int> en(n+1);
    iota(en.begin(), en.end(), 0);

    for (int i = 0; (1<<i) <=k; i++) {
        if ((1<<i) & k) {
            for (int j = 0; j <= n; j++) {
                ans[j] += wei[i][en[j]];
                en[j] = tra[i][en[j]];
            }
        }
    }

    long long mi = inf;
    int beg = -1;

    for (int i = 0; i < n; i++) {
        if (mi > ans[i] && sz[id[i]] + dist[i] >= k) {
            mi = ans[i];
            beg = i;
        }
    }

    if (mi >= inf) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < k; i++) {
        cout << beg << ' ';
        beg = tra[0][beg];
    }
    cout << '\n';
}
