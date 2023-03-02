#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> lixo(n);
        for(int& x : lixo)
            scanf("%d", &x);
        printf("1 %d\n", n);
    }
}
