#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a, b;
        bool tem = 0;
        for(int i = 0; i < n; i++) {
            int v; scanf("%d", &v);
            tem |= v != 0;
            if(v >= 0) a.push_back(v);
            else b.push_back(v);
        }
        if(!tem) puts("NO");
        else {
            puts("YES");
            int s = 0;
            while(a.size() + b.size()) {
                if(s <= 0)
                    printf("%d ", a.back()), s += a.back(), a.pop_back();
                else
                    printf("%d ", b.back()), s += b.back(), b.pop_back();
            }
            puts("");
        }
    }
}
