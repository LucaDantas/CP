#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 101, MAGIC = 5e5+10;

int dp[maxn][MAGIC];

int n;

vector<int> a;

long long solve(int i, long long val) {
    if(i == n) return val;
    if(val < MAGIC && dp[i][val] != -1) return dp[i][val];
    long long ans = solve(i+1, val) - solve(i+1, val / a[i]);
    if(val < MAGIC) dp[i][val] = ans;
    return ans;
}

int main() {
    memset(dp, -1, sizeof dp);
    long long val;
    scanf("%lld %d", &val, &n);
    a.resize(n);
    for(int& x : a)
        scanf("%d", &x);
    sort(a.begin(), a.end(), greater<>());
    printf("%lld\n", solve(0, val));
}
