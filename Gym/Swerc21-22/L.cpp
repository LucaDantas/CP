#include<bits/stdc++.h>
using namespace std;

int c[22][360], l[22][360];
bool mark[22][360];

bool dfs(int x, int y) {
    if(x == 20) return 1;
    if(mark[x][y]) return 0;
    bool ok = 0;
    mark[x][y] = 1;

    if(!l[x][y])
        ok |= dfs(x, (y+359) % 360);
    if(!l[x][(y+1) % 360])
        ok |= dfs(x, (y+1) % 360);
    if(!c[x+1][y])
        ok |= dfs(x+1, y);
    if(!c[x][y] && x)
        ok |= dfs(x-1, y);

    return ok;
}

void solve() {
    memset(c, 0, sizeof c);
    memset(l, 0, sizeof l);
    memset(mark, 0, sizeof mark);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string type;
        cin >> type;
        if (type == "C") {
            int r, d1, d2;
            cin >> r >> d1 >> d2;
            if (d1 < d2) {
                for (int j = d1; j < d2; j++) {
                    c[r][j] = 1;
                }
            } else {
                for (int j = d1; j < 360; j++) {
                    c[r][j] = 1;
                }
                for (int j = 0; j < d2; j++) {
                    c[r][j] = 1;
                }
            }
        } if (type == "S")  {
            int r1, r2, d;
            cin >> r1 >> r2 >> d;
            for (int j = r1; j < r2; j++) {
                l[j][d] = 1;
            }
        }
    }
    if (dfs(0,0)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    int tt;
    cin >> tt;
    while(tt--) {
        solve();
    }
}
