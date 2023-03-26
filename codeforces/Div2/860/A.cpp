#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        int mx[2]{}, last[2]{};
        vector<int> a(n), b(n);
        for(int& x : a)
            scanf("%d", &x);
        for(int& x : b)
            scanf("%d", &x);
        for(int i = 0; i < n; i++) {
            last[0] = a[i], last[1] = b[i];
            if(last[0] > last[1])
                swap(last[0], last[1]);
            mx[0] = max(mx[0], last[0]);
            mx[1] = max(mx[1], last[1]);
        }
        puts(last[0] == mx[0] && last[1] == mx[1] ? "YES" : "NO");
    }
}
