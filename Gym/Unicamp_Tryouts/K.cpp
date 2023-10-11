#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

array<int,3> it[maxn];

int main() {
    int n; scanf("%d", &n);
    for(int i = 0, l, r; i < n; i++)
        scanf("%d %d", &l, &r), it[i] = {l, r, i+1};
    sort(it, it+n);
    priority_queue<int, vector<int>, greater<int>> q;
    pair<int,int> ans = {0, 0}, now = {0, 0};
    for(int i = 0; i < n; i++) {
        auto [l, r, id] = it[i];
        while(q.size() && q.top() < l)
            --now.first, q.pop();
        ++now.first, now.second = l;
        ans = max(ans, now);
        q.push(r);
    }
    printf("%d\n", ans.first);
    for(int i = 0; i < n; i++)
        if(it[i][0] <= ans.second && it[i][1] >= ans.second)
            printf("%d ", it[i][2]);
    puts("");
}
