#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int main() {
    int n;
    cin >> n;
    vector<int> gr(n);
    vector<bool> tp(n);
    vector<bool> appeared(N);
    for (int i = 0; i < n; i++) {
        string s; 
        cin >> s;
        if (s[0] == 'e') tp[i] = 1;
        gr[i] = atoi(s.substr(1, s.size()-1).c_str());
        appeared[gr[i]] = 1;
    }
    // for (int i = 0; i < n; i++) {
    //     cout << tp[i] << ' ' << gr[i] << '\n';
    // }

    vector<int> mi(N);
    vector<int> cur(N);
    
    for (int i = 0; i < n; i++) {
        cur[gr[i]] += (tp[i] == 0) ? 1 : -1;
        mi[gr[i]] = min(mi[gr[i]], cur[gr[i]]);
    }

    // for (int i = 0; i < 43; i++) {
    //     cout << mi[i] << ' ' << cur[i] << '\n';
    // }
    int curSat = 0;
    int ansPos = 0;

    for (int i = 0; i < N; i++) {
        if (appeared[i] && cur[i] == 0 && mi[i] >= 0) {
            curSat++;
        }
    }
    int bestSat = curSat;
    // int ans = -2;
    // int ansPos;

    // int curEq = 0;


    for (int i = 0; i < n - 1; i++) {
        if (appeared[gr[i]] && cur[gr[i]] == 0 && mi[gr[i]] == 0 && tp[i] == 0) {
            curSat--;
        }
        if (appeared[gr[i]] && cur[gr[i]] == 0 && mi[gr[i]] == -1 && tp[i] == 1) {
            curSat++;
        }
        if (bestSat < curSat) {
            bestSat = curSat;
            ansPos = i + 1;
        }
        mi[gr[i]] += (tp[i] == 0) ? -1 : 1;
    } 
    cout << ansPos + 1 << ' ' << bestSat << '\n';
}
