#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d; scanf("%d %d", &n, &d);
    if(1ll*n*d > 1ll*n*(n-1)/2) return puts("No"), 0;
    puts("Yes");
    for(int i = 0; i < n; i++)
        for(int j = 1; j <= d; j++)
            printf("%d %d\n", i+1, (i+j)%n + 1);
}
