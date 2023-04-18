#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n), cnt(n);
        for(int& x : a) {
            scanf("%d", &x);
            if(x < n)
                cnt[x]++;
        }
        int mex = 0;
        for(; mex < n && cnt[mex]; mex++);
        if(mex == n) { puts("NO"); continue; }
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i < n && a[i] != mex+1; i++)
            if(a[i] < n) cnt[a[i]]++;
        for(int i = n-1; i >= 0 && a[i] != mex+1; i--)
            if(a[i] < n) cnt[a[i]]++;
        cnt[mex] = 1;
        int mex2 = 0;
        for(; mex2 < n && cnt[mex2]; mex2++);
        puts(mex2 == mex+1 ? "YES" : "NO");
    }
}
