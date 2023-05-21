#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vector<int> color(n, -1);
    vector<bool> bothHands(n, false);
    vector<long long> period(n, 0);
    vector<int> colors;

    for (int i = 0; i < n; i++) {
        if (v[i] == 0) continue;
        if (color[i] != -1) continue;
        colors.push_back(i);
        long long curPos = i;
        while(color[curPos % n] == -1) {
            color[curPos % n] = i;
            curPos += v[curPos % n];
            if (curPos % 2 != i % 2) {
                bothHands[i] = 1;
            }
        }
        period[i] = curPos - i;
    }

    long long odd = 0;
    long long even = 0;
    long long both = 0;

    for (int c : colors) {
        long long numBall = period[c] / n;
        if (bothHands[c] == 1) {
            both += numBall;
        } else {
            if (n % 2 == 1) {
                even += numBall / 2;
                odd += numBall / 2;
            } else {
                if (c % 2 == 0) {
                    odd += numBall;
                } else {
                    even += numBall;
                }
            }
        }
    }
    cout << odd << ' ' << even << ' ' << both << '\n';
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
