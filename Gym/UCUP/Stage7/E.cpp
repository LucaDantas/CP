#include<bits/stdc++.h>
using namespace std;

void solve() {
    int l, r;
    cin >> l >> r;
    if (l % 2 == 0 && r % 2 == 0) {
        cout << -1 << '\n';
        return;
    }
    if (r == l) {
        if (l == 1) {
            cout << l << '\n';
            return;
        } else {
            cout << -1 << '\n';
            return;
        }
    } 
    if ((r - l + 1) % 2 == 0) {
        for (int i = l; i < r; i += 2) {
            cout << i + 1 << ' ' << i << ' ';  
        }
        cout << '\n';
        return;
    } else {
        cout << l + 1 << ' ' << l + 2 << ' ' << l << ' ';
        l = l + 3;
        for (int i = l; i < r; i += 2) {
            cout << i + 1 << ' ' << i << ' ';  
        }
        cout << '\n';

        return;
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
