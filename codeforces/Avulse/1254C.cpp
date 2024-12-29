#include <bits/stdc++.h>
using namespace std;

int cross(int a, int b) {
    printf("2 1 %d %d\n", a, b);
    fflush(stdout);
    int sign; scanf("%d", &sign);
    return sign;
}

long long area(int a, int b) {
    printf("1 1 %d %d\n", a, b);
    fflush(stdout);
    long long area; scanf("%lld", &area);
    return area;
}

int main() {
    int n; scanf("%d", &n);
    // primeiro acha o primeiro cara imediatamente depois de mim
    int segundo = 2;
    for(int i = 3; i <= n; i++)
        if(cross(segundo, i) == -1)
            segundo = i;

    vector<long long> dist(n+1);
    for(int i = 2; i <= n; i++) if(i != segundo)
        dist[i] = area(segundo, i); // sempre usa o 1 como base

    int maior = max_element(dist.begin(), dist.end()) - dist.begin();

    vector<int> lado[2];

    for(int i = 2; i <= n; i++) if(i != maior && i != segundo)
        lado[cross(maior, i) == -1].push_back(i);

    for(int k : {0, 1})
        sort(lado[k].begin(), lado[k].end(), [&](int a, int b){
                return dist[a] < dist[b];
            });

    vector<int> ans = {1, segundo};

    for(int x : lado[1])
        ans.push_back(x);

    ans.push_back(maior);

    reverse(lado[0].begin(), lado[0].end());
    for(int x : lado[0])
        ans.push_back(x);

    putchar('0');
    for(int x : ans)
        printf(" %d", x);
    puts("");
}
