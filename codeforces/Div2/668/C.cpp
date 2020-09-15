#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e5+10;

char s[maxn];

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n, k; scanf("%d %d", &n, &k);
        scanf(" %s", s);
        vector<int> mark(k, -1);
        bool ok = 1;
        for(int i = 0; i < n; i++) {
            if(s[i] == '?') continue;
            int here = s[i] - '0';
            if(mark[i%k] == -1) mark[i%k] = here;
            else if(mark[i%k] != here) ok = 0;
        }
        int soma = 0, joker = 0;
        for(int i = 0; i < k; i++) {
            if(mark[i] == -1) joker++;
            else soma += mark[i];
        }
        if(soma < k/2) soma += min(k/2 - soma, joker);
        if(soma != k/2) ok = 0;
        puts(ok?"YES":"NO");
    }
}