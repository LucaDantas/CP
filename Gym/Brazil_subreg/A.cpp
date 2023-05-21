#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    bool added = 0, last = 0;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        char c; scanf(" %c", &c);
        if(c == 'a')
            if(last) ans += 1 + !added, added = 1;
            else last = 1;
        else last = 0, added = 0;
    }
    printf("%d\n", ans);
}
