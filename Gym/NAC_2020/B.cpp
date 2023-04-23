#include<bits/stdc++.h>
using namespace std;

int n, k;

char gr[5][5]; 
char temp[5][5];

vector<int> len(5);
int ans = 0;

int check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (gr[i][j] == '.') continue;
            if (gr[i][j] != temp[i][j]) return 0;
        }
    }
    return 1;
}

bool place(int r, int c, int orrr, int l) {
    int dr = 0;
    int dc = 0;
    if (orrr == 0) dr = 1;
    if (orrr == 1) dc = 1;

    for (int i = 0; i < l; i++) {
        int rr = r + i * dr;
        int cc = c + i * dc;
        if (rr >= n || cc >=n) return false;
        if (temp[rr][cc] == 'O') return false;
    }
    for (int i = 0; i < l; i++) {
        int rr = r + i * dr;
        int cc = c + i * dc;
        temp[rr][cc] = 'O';
    }
    return true;
}

void rem(int r, int c, int orrr, int l) {
    int dr = 0;
    int dc = 0;
    if (orrr == 0) dr = 1;
    if (orrr == 1) dc = 1;
    
    for (int i = 0; i < l; i++) {
        int rr = r + i * dr;
        int cc = c + i * dc;
        temp[rr][cc] = 'X';
    }
}

void solve(int i) {
    // cout << i << '\n';
    // for (int j = 0; j < n; j++) {
    //     for (int k = 0; k < n; k++) {
    //         cout << temp[j][k];
    //     }
    //     cout << '\n';
    // }
    if (i == k) {
        ans += check();
        return;
    } else {
        int orr;
        int l = len[i];
        if (l == 1) orr = 0;
        else orr = 1;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                for (int orrr = 0; orrr <= orr; orrr++) {
                    if (place(r, c, orrr, l)) {
                        solve(i+1);
                        rem(r, c, orrr, l);
                    }
                }
            }
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> gr[i][j];
            temp[i][j] = 'X';
        }
    }

    for (int i = 0; i < k; i++) {
        cin >> len[i];
    }

    solve(0);

    cout << ans << '\n';
}