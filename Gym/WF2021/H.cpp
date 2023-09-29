#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e6+10;

pair<int,int> a[maxn];
char s[maxn*10];
vector<int> pos, neg;

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf(" %s", s);
        int mn = 0, soma = 0;
        for(int j = 0; j < (int)(strlen(s)); j++)
            soma += (s[j] == '(' ? 1 : -1), mn = min(mn, soma);
        a[i] = {-mn, soma};
        if(soma >= 0)
            pos.push_back(i);
        else
            neg.push_back(i);
    }
    sort(pos.begin(), pos.end(), [](int x, int y){
        return a[x].first < a[y].first;
    });
    sort(neg.begin(), neg.end(), [](int x, int y){
        return a[x].first + a[x].second > a[y].first + a[y].second;
    });
    int soma = 0;
    bool ok = 1;
    for(int x : pos)
        ok &= soma >= a[x].first, soma += a[x].second;
    for(int x : neg)
        ok &= soma >= a[x].first, soma += a[x].second;
    ok &= soma == 0;
    if(!ok) puts("impossible");
    else {
        for(int x : pos)
            printf("%d\n", x+1);
        for(int x : neg)
            printf("%d\n", x+1);
    }
}
