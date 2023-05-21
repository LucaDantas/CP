#include<bits/stdc++.h>
using namespace std;
const long long inf = (long long) 1e18 + 10;
const int inf1 = (int) 1e9 + 10;
#define int long long
#define dbl long double
#define endl '\n'
#define sc second
#define fr first
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
const int maxn = 11;

int n, k, m, c[maxn], d[(1<<maxn)][(1<<maxn)], blks[maxn], hascol[maxn];

void solve() {
    cin >> n >> k >> m;
    int msk0 = 0;
    for(int i = 0; i < n; i++) {
        cin >> c[i]; c[i]--;
        if(c[i] == 0) msk0+= (1<<i);
        hascol[c[i]]+= (1<<i);
    }

    for(int i = 0; i < m; i++) {
        int qt; cin >> qt;
        while(qt--) {
            int x; cin >> x; x--;
            blks[i]+= (1<<x);
        }
    }
    for(int i = 0; i < (1<<n); i++) {
        for(int j = 0; j < (1<<m); j++) {
            d[i][j] = -1;
        }
    }
    d[msk0][0] = 0;
    queue<pair<int,int>> q;
    q.push(mp(msk0,0));
    while(q.size()) {
        int mskrg = q.front().fr;
        int mskeq = q.front().sc;
        q.pop();

        for(int i = 0; i < m; i++) {
            int mskeq1 = mskeq^(1<<i);
            if(d[mskrg][mskeq1] == -1) {
                d[mskrg][mskeq1] = d[mskrg][mskeq]+1;
                q.push(mp(mskrg,mskeq1));
            }
        }

        int mskop = (1<<n)-1;
        for(int i = 0; i < m; i++) {
            if((1<<i)&mskeq) {
                mskop-= mskop&blks[i];
            }
        }
        for(int i = 0; i < k; i++) {
            int mskrg1 = mskrg;
            mskrg1-= mskrg1&mskop;
            mskrg1|= mskop&hascol[i];
            if(d[mskrg1][mskeq] == -1) {
                d[mskrg1][mskeq] = d[mskrg][mskeq]+1;
                q.push(mp(mskrg1,mskeq));
            }
        }
    }

    cout << d[(1<<n)-1][0] << endl;
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0);

    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    int tt = 1;
    // cin >> tt;
    while(tt--) {
        solve();
    }

}
