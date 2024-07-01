#include<bits/stdc++.h>
using namespace std;

// int upper(char c, int l, int r) {

// }
const int N = 1e6 + 5;

int binJmp[N][20];
char let[N];
int nxt[N];
int sa[N];

char get(int wordInd, int charPos) {
    for (int i = 0; i < 20; i++) {
        if (charPos & (1<<i)) {
            wordInd = binJmp[wordInd][i];
        }
    }
    return let[wordInd];
}

int lower(char c, int letPos, int ll, int rr) {
    while (ll < rr) {
        int mid = (ll + rr) / 2;
        if (get(sa[mid], letPos) < c) ll = mid + 1;
        else rr = mid;
    }
    if (get(sa[ll], letPos) != c) {
        return -1;
    } else {
        return ll;
    }
}

int upper(char c, int letPos, int ll, int rr) {
    while (ll < rr) {
        int mid = (ll + rr + 1) / 2;
        if (c < get(sa[mid], letPos)) rr = mid - 1;
        else ll = mid;
    }
    if (get(sa[ll], letPos) != c) {
        return -1;
    } else {
        return ll;
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    
    let[0] = 'A' - 1;
    for (int i = 1; i <= n; i++) {
        cin >> let[i] >> nxt[i];
    }
    for (int i = 1; i <= n; i++) {
        binJmp[i][0] = nxt[i];
    }

    for (int j = 0; j < 20; j++) {
        binJmp[0][j] = 0;
    }

    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= n; i++) {
            binJmp[i][j] = binJmp[binJmp[i][j-1]][j-1];
        }
    }

    vector<int> w(max(N, 28)), w1(max(N, 28)), stInd(N);
    vector<queue<int>> ord(N);

    for (int i = 1; i <= n; i++) {
        w[i] = let[i] - 'A' + 1;
    }

    for (int i = 0; i < n; i++) sa[i] = i+1;
    // int len = 1; 
    int lenLog = 0;
    while ((1<<lenLog) < n) {
        fill(stInd.begin(), stInd.end(), 0);
        for (int i = 1; i <= n; i++) {
            stInd[w[i]+1]++;
        }
        for (int i = 1; i < N-1; i++) {
            stInd[i] += stInd[i-1];
        }
        for (int i = 1; i <= n; i++) {
            int curW = (binJmp[i][lenLog] == 0) ? 0 : w[binJmp[i][lenLog]];
            ord[curW].push(i);
        }

        for (int curW = 0; curW < N; curW++) {
            if (!ord[curW].empty()) {
                // cout << curW << ": ";
                // while(!ord[curW].empty()) {
                //     cout << ord[curW].front() << ' ';
                //     ord[curW].pop();
                // }
                // cout << '\n';
                while(!ord[curW].empty()) {
                    int curInd = ord[curW].front();
                    sa[stInd[w[curInd]]] = curInd;
                    stInd[w[curInd]]++;
                    ord[curW].pop();
                    // cout << curInd << ' ' << curW << "What\n";
                }
            }
        }
        w1[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            int lastW1 = (binJmp[sa[i-1]][lenLog] == 0) ? 0 : w[binJmp[sa[i-1]][lenLog]];
            int lastW2 = (binJmp[sa[i]][lenLog] == 0) ? 0 : w[binJmp[sa[i]][lenLog]];
            w1[sa[i]] = w1[sa[i-1]]+1;
            if (w[sa[i]] == w[sa[i-1]] && lastW1 == lastW2) {
                w1[sa[i]]--;
            }
        }
        swap(w, w1);
        lenLog++;
    }

    // for (int i = 0; i < n; i++) {
    //     cout << sa[i] << '\n';
    // }

    while(q--) {
        string qu;
        cin >> qu;
        int l = 0, r = n-1;
        // cout << lower(qu[0], 0, l, r) << '\n';
        // cout << upper(qu[0], 0, l, r) << '\n';
        bool broken = false;
        for (int i = 0; i < qu.size(); i++) {
            int ll = lower(qu[i], i, l, r);
            // cout << ll << "This is LL\n";
            if (ll == -1) {
                cout << 0 << '\n';
                broken = true;
                break;
            }
            int rr = upper(qu[i], i, l, r);
            if (rr == -1) {
                cout << 0 << '\n';
                broken = true;
                break;
            }
            l = ll;
            r = rr;
            // cout << l << ' ' << r << '\n';
            //what
        }

        if (!broken) {
            cout << r - l + 1 << '\n';
        }
    }
}
