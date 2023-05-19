#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    if (n == k) {
        if (n == 1) {
            cout << "YES\n";
            cout << 0 << '\n';
            return 0;
        }
        cout << "NO\n";
        return 0;
    }
    vector<pair<int, int> > ans;
    if (k % 2 == 1) {
        for (int i = 2; i <= n - k + 1; i++) {
            for (int j = 1;  j < i; j++) ans.push_back({j, i});
        }
        for (int i = n - k + 2; i <= n; i++) {
            if (i % 2 != (n - k + 2) % 2) {
                for (int j = 1; j < i; j++) ans.push_back({j, i});
            }
        }
    } else {
        for (int i = 1; i < n - k + 2; i++) {
            ans.push_back({i, n-k+2});
        }
        for (int i = n - k + 3; i <= n; i++) {
            if (i % 2 != (n - k + 3) % 2) {
                for (int j = 1; j < i; j++) ans.push_back({j, i});
            }
        }
    }
    cout << "YES\n";
    cout << ans.size() << '\n';
    for (pair<int, int> p : ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}
