#include <bits/stdc++.h>
using namespace std;

#define sz(a) (int)(a.size())
#define all(a) a.begin(), a.end()

using ll = long long;

unordered_set<ll> mp;

int d[42][42], r[42][42];

vector<ll> pos[42][42], rev[42][42];

vector<ll> apply(vector<ll> a, int v) {
    vector<ll> v1, v2;
    for(ll &x : a) {
        if(x & (1ll << v))
            v1.push_back(x);
        else
            v2.push_back(x | (1ll << v));
    }
    a.clear();
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(a));
    a.erase(unique(all(a)), a.end());
    return a;
}

vector<ll> merge(vector<ll> a, vector<ll> b) {
    vector<ll> ans;
    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ans));
    ans.erase(unique(all(ans)), ans.end());
    return ans;
}

bool check(ll mask, int sz) {
    return mp.find(((1ll << sz)-1) & (~mask)) != mp.end();
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        for(int i = 0; i < n-1; i++)
            for(int j = 0; j < n; j++)
                scanf("%d", &d[i][j]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n-1; j++)
                scanf("%d", &r[i][j]);

        pos[0][0].push_back(0);
        for(int j = 1; j < n; j++)
            pos[0][j] = apply(pos[0][j-1], r[0][j-1]);
        for(int i = 1; i < n; i++)
            pos[i][0] = apply(pos[i-1][0], d[i-1][0]);

        int sz = 2*n/3;

        for(int i = 1; i < n; i++)
            for(int j = 1; j < n && i+j <= sz; j++)
                pos[i][j] = merge(apply(pos[i-1][j], d[i-1][j]), apply(pos[i][j-1], r[i][j-1]));

        rev[n-1][n-1].push_back(0);
        for(int j = n-2; j >= 0; j--)
            rev[n-1][j] = apply(rev[n-1][j+1], r[n-1][j]);
        for(int i = n-2; i >= 0; i--)
            rev[i][n-1] = apply(rev[i+1][n-1], d[i][n-1]);

        for(int i = n-2; i >= 0; i--)
            for(int j = n-2; j >= 0 && i + j >= sz; j--)
                rev[i][j] = merge(apply(rev[i+1][j], d[i][j]), apply(rev[i][j+1], r[i][j]));

        int cur = 0;
        for(int i = 0; i <= sz; i++) {
            int j = sz - i; // they must add up to sz
            mp.clear();
            mp.insert(0);
            for(ll chegando : pos[i][j]) {
                for(ll mask = chegando; mask > 0; --mask, mask &= chegando)
                    mp.insert(mask);
            }
            for(ll saindo : rev[i][j]) {
                while(check(saindo, cur+1))
                    cur++;
            }
        }
        printf("%d\n", cur);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                pos[i][j].clear(), rev[i][j].clear();
    }
}
